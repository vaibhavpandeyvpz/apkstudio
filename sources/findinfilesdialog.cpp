#include <QApplication>
#include <QBrush>
#include <QColor>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFont>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QListWidgetItem>
#include <QMap>
#include <QMessageBox>
#include <QPalette>
#include <QPushButton>
#include <QRegularExpression>
#include <QScrollBar>
#include <QSizePolicy>
#include <QStringConverter>
#include <QTextBlock>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QTextStream>
#include <QTimer>
#include <QVBoxLayout>
#include "findinfilesdialog.h"
#include "mainwindow.h"
#include "sourcecodeedit.h"

FindInFilesDialog::FindInFilesDialog(MainWindow *parent)
    : QDialog(parent), m_MainWindow(parent), m_SearchRoot()
{
    setWindowTitle(tr("Find in Files"));
    setMinimumSize(512, 384);
    resize(640, 480);
    
#ifdef Q_OS_WIN
    setWindowIcon(QIcon(":/icons/fugue/binocular.png"));
#endif
    
    buildUI();
    
    // Connect search button and Enter key
    connect(m_EditSearch, &QLineEdit::returnPressed, this, &FindInFilesDialog::handleSearch);
}

void FindInFilesDialog::buildUI()
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(8, 8, 8, 8);
    mainLayout->setSpacing(8);
    
    // Search input and options
    auto searchLayout = new QHBoxLayout;
    searchLayout->addWidget(new QLabel(tr("Search:"), this));
    m_EditSearch = new QLineEdit(this);
    m_EditSearch->setPlaceholderText(tr("Enter search term..."));
    searchLayout->addWidget(m_EditSearch);
    
    auto searchButton = new QPushButton(tr("Search"), this);
    connect(searchButton, &QPushButton::clicked, this, &FindInFilesDialog::handleSearch);
    searchLayout->addWidget(searchButton);
    mainLayout->addLayout(searchLayout);
    
    // Options group
    auto optionsGroup = new QGroupBox(tr("Options"), this);
    optionsGroup->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    auto optionsLayout = new QHBoxLayout(optionsGroup);
    m_CheckCase = new QCheckBox(tr("Case Sensitive"), this);
    m_CheckWhole = new QCheckBox(tr("Whole Words"), this);
    m_CheckRegexp = new QCheckBox(tr("Use Regexp"), this);
    optionsLayout->addWidget(m_CheckCase);
    optionsLayout->addWidget(m_CheckWhole);
    optionsLayout->addWidget(m_CheckRegexp);
    optionsLayout->addStretch();
    mainLayout->addWidget(optionsGroup);
    
    // Splitter for results and preview
    m_Splitter = new QSplitter(Qt::Horizontal, this);
    
    // Results list
    m_ResultsList = new QListWidget(this);
    m_ResultsList->setAlternatingRowColors(true);
    connect(m_ResultsList, &QListWidget::itemClicked, this, &FindInFilesDialog::onResultClicked);
    connect(m_ResultsList, &QListWidget::itemSelectionChanged, this, &FindInFilesDialog::handleResultSelectionChanged);
    m_Splitter->addWidget(m_ResultsList);
    
    // Preview text
    m_PreviewText = new QTextEdit(this);
    m_PreviewText->setReadOnly(true);
    m_PreviewText->setFont(QFont("Consolas", 10));
    m_Splitter->addWidget(m_PreviewText);
    
    m_Splitter->setStretchFactor(0, 1);
    m_Splitter->setStretchFactor(1, 1);
    mainLayout->addWidget(m_Splitter, 1); // Add with stretch factor 1 to fill remaining space
    
    // Progress bar
    m_ProgressBar = new QProgressBar(this);
    m_ProgressBar->setVisible(false);
    m_ProgressBar->setMinimum(0);
    m_ProgressBar->setMaximum(0); // Indeterminate
    m_ProgressBar->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    mainLayout->addWidget(m_ProgressBar);
    
    // Buttons
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Close, this);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    mainLayout->addWidget(buttonBox);
    
    // Status label
    m_LabelStatus = new QLabel(tr("Ready"), this);
    m_LabelStatus->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
    mainLayout->addWidget(m_LabelStatus);
    
    setLayout(mainLayout);
}

void FindInFilesDialog::setSearchRoot(const QString &rootPath)
{
    m_SearchRoot = rootPath;
}

QStringList FindInFilesDialog::getTextFileExtensions()
{
    // Match the extensions used in MainWindow
    return QStringList() << "java" << "html" << "properties" << "smali" 
                        << "txt" << "xml" << "yaml" << "yml" << "cpp" 
                        << "h" << "c" << "hpp" << "cc" << "cxx" << "js" 
                        << "ts" << "json" << "css" << "md" << "sh" << "bat" 
                        << "cmake" << "py" << "gradle" << "kt" << "pro" 
                        << "pri" << "qrc" << "ui" << "qml";
}

bool FindInFilesDialog::isTextFile(const QString &filePath)
{
    QFileInfo info(filePath);
    QString extension = info.suffix().toLower();
    return getTextFileExtensions().contains(extension);
}

void FindInFilesDialog::scanDirectory(const QString &dirPath, const QString &searchTerm,
                                     bool caseSensitive, bool wholeWords, bool useRegexp)
{
    QDir dir(dirPath);
    if (!dir.exists()) {
        return;
    }
    
    QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot, 
                                              QDir::Name | QDir::DirsFirst);
    
    for (const QFileInfo &info : entries) {
        if (info.isDir()) {
            // Recursively scan subdirectories
            scanDirectory(info.absoluteFilePath(), searchTerm, caseSensitive, wholeWords, useRegexp);
        } else if (info.isFile() && isTextFile(info.absoluteFilePath())) {
            // Search in text file
            QFile file(info.absoluteFilePath());
            if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                continue;
            }
            
            QTextStream in(&file);
            in.setEncoding(QStringConverter::Utf8);
            int lineNumber = 1;
            
            QRegularExpression regex;
            if (useRegexp) {
                QRegularExpression::PatternOptions options = QRegularExpression::NoPatternOption;
                if (!caseSensitive) {
                    options |= QRegularExpression::CaseInsensitiveOption;
                }
                regex = QRegularExpression(searchTerm, options);
                if (!regex.isValid()) {
                    continue;
                }
            }
            
            while (!in.atEnd()) {
                QString line = in.readLine();
                bool found = false;
                int matchStart = -1;
                int matchLength = 0;
                
                if (useRegexp) {
                    QRegularExpressionMatch match = regex.match(line);
                    if (match.hasMatch()) {
                        found = true;
                        matchStart = match.capturedStart();
                        matchLength = match.capturedLength();
                    }
                } else {
                    QString searchText = searchTerm;
                    QString lineText = line;
                    
                    if (!caseSensitive) {
                        searchText = searchText.toLower();
                        lineText = lineText.toLower();
                    }
                    
                    int pos = lineText.indexOf(searchText);
                    if (pos >= 0) {
                        if (wholeWords) {
                            // Check if it's a whole word
                            bool isWholeWord = true;
                            if (pos > 0) {
                                QChar prev = line.at(pos - 1);
                                if (prev.isLetterOrNumber() || prev == '_') {
                                    isWholeWord = false;
                                }
                            }
                            if (pos + searchText.length() < line.length()) {
                                QChar next = line.at(pos + searchText.length());
                                if (next.isLetterOrNumber() || next == '_') {
                                    isWholeWord = false;
                                }
                            }
                            if (!isWholeWord) {
                                pos = -1;
                            }
                        }
                        
                        if (pos >= 0) {
                            found = true;
                            matchStart = pos;
                            matchLength = searchTerm.length();
                        }
                    }
                }
                
                if (found) {
                    SearchMatch match;
                    match.filePath = info.absoluteFilePath();
                    match.lineNumber = lineNumber;
                    match.lineText = line;
                    match.matchStart = matchStart;
                    match.matchLength = matchLength;
                    m_Matches.append(match);
                }
                
                lineNumber++;
            }
            
            file.close();
        }
    }
}

void FindInFilesDialog::performSearch()
{
    QString searchTerm = m_EditSearch->text().trimmed();
    if (searchTerm.isEmpty()) {
        m_LabelStatus->setText(tr("Please enter a search term."));
        return;
    }
    
    if (m_SearchRoot.isEmpty()) {
        m_LabelStatus->setText(tr("No project folder selected."));
        return;
    }
    
    m_Matches.clear();
    m_ResultsList->clear();
    m_PreviewText->clear();
    
    m_ProgressBar->setVisible(true);
    m_LabelStatus->setText(tr("Searching..."));
    QApplication::processEvents();
    
    bool caseSensitive = m_CheckCase->isChecked();
    bool wholeWords = m_CheckWhole->isChecked();
    bool useRegexp = m_CheckRegexp->isChecked();
    
    if (useRegexp) {
        QRegularExpression testRegex(searchTerm);
        if (!testRegex.isValid()) {
            m_LabelStatus->setText(tr("Invalid regular expression: %1").arg(testRegex.errorString()));
            m_ProgressBar->setVisible(false);
            return;
        }
    }
    
    scanDirectory(m_SearchRoot, searchTerm, caseSensitive, wholeWords, useRegexp);
    
    m_ProgressBar->setVisible(false);
    updateResults();
}

void FindInFilesDialog::updateResults()
{
    m_ResultsList->clear();
    
    int matchCount = m_Matches.size();
    if (matchCount == 0) {
        m_LabelStatus->setText(tr("No matches found."));
        return;
    }
    
    // Group matches by file
    QMap<QString, QList<SearchMatch>> fileMatches;
    for (const SearchMatch &match : m_Matches) {
        fileMatches[match.filePath].append(match);
    }
    
    // Add items to list
    for (auto it = fileMatches.begin(); it != fileMatches.end(); ++it) {
        QString filePath = it.key();
        QFileInfo fileInfo(filePath);
        QString fileName = fileInfo.fileName();
        QString relativePath = QDir(m_SearchRoot).relativeFilePath(filePath);
        
        // File header item
        auto headerItem = new QListWidgetItem(QString("%1 (%2 matches)").arg(relativePath).arg(it.value().size()));
        headerItem->setData(Qt::UserRole, QVariant::fromValue<QString>(QString())); // Empty string indicates header
        QFont headerFont = headerItem->font();
        headerFont.setBold(true);
        headerItem->setFont(headerFont);
        // Use palette color that adapts to theme (AlternateBase for light gray in light mode, dark gray in dark mode)
        headerItem->setBackground(QBrush(palette().color(QPalette::AlternateBase)));
        headerItem->setForeground(QBrush(palette().color(QPalette::Text)));
        m_ResultsList->addItem(headerItem);
        
        // Match items
        for (const SearchMatch &match : it.value()) {
            QString displayText = QString("  %1: %2").arg(match.lineNumber).arg(match.lineText.trimmed());
            if (displayText.length() > 100) {
                displayText = displayText.left(100) + "...";
            }
            auto item = new QListWidgetItem(displayText);
            item->setData(Qt::UserRole, QVariant::fromValue<SearchMatch>(match));
            // Use neutral styling - Base background and Text foreground, normal font weight
            item->setBackground(QBrush(palette().color(QPalette::Base)));
            item->setForeground(QBrush(palette().color(QPalette::Text)));
            QFont itemFont = item->font();
            itemFont.setBold(false);
            item->setFont(itemFont);
            m_ResultsList->addItem(item);
        }
    }
    
    m_LabelStatus->setText(tr("%1 match%2 in %3 file%4")
                          .arg(matchCount)
                          .arg(matchCount == 1 ? "" : "es")
                          .arg(fileMatches.size())
                          .arg(fileMatches.size() == 1 ? "" : "s"));
}

void FindInFilesDialog::handleSearch()
{
    performSearch();
}

void FindInFilesDialog::handleResultSelectionChanged()
{
    auto item = m_ResultsList->currentItem();
    if (!item) {
        m_PreviewText->clear();
        return;
    }
    
    QVariant data = item->data(Qt::UserRole);
    if (data.canConvert<SearchMatch>()) {
        SearchMatch match = data.value<SearchMatch>();
        
        // Load file content for preview
        QFile file(match.filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            in.setEncoding(QStringConverter::Utf8);
            QString content = in.readAll();
            file.close();
            
            // Show context around the match (5 lines before and after)
            QStringList lines = content.split('\n');
            int startLine = qMax(0, match.lineNumber - 6);
            int endLine = qMin(lines.size(), match.lineNumber + 5);
            
            QString preview;
            for (int i = startLine; i < endLine; i++) {
                QString lineNum = QString::number(i + 1).rightJustified(4, ' ');
                QString line = lines[i];
                if (i == match.lineNumber - 1) {
                    preview += QString("%1: %2\n").arg(lineNum).arg(line);
                } else {
                    preview += QString("%1: %2\n").arg(lineNum).arg(line);
                }
            }
            
            m_PreviewText->setPlainText(preview);
            
            // Highlight the matching line
            QTextCursor cursor = m_PreviewText->textCursor();
            int targetLine = match.lineNumber - startLine - 1;
            cursor.movePosition(QTextCursor::Start);
            for (int i = 0; i < targetLine; i++) {
                cursor.movePosition(QTextCursor::Down);
            }
            cursor.movePosition(QTextCursor::EndOfLine);
            m_PreviewText->setTextCursor(cursor);
            m_PreviewText->ensureCursorVisible();
        }
    } else {
        m_PreviewText->clear();
    }
}

void FindInFilesDialog::onResultClicked(QListWidgetItem *item)
{
    if (!item) {
        return;
    }
    
    QVariant data = item->data(Qt::UserRole);
    if (!data.canConvert<SearchMatch>()) {
        return; // Header item, do nothing
    }
    
    SearchMatch match = data.value<SearchMatch>();
    
    // Open file in main window
    if (m_MainWindow) {
        // Open the file first
        m_MainWindow->openFile(match.filePath);
        
        // Wait a bit for the file to open, then navigate to the line
        QTimer::singleShot(100, [this, match]() {
            auto widget = m_MainWindow->findTabWidget(match.filePath);
            if (widget) {
                auto edit = dynamic_cast<SourceCodeEdit *>(widget);
                if (edit) {
                    edit->gotoLine(match.lineNumber);
                    
                    // Highlight the match
                    QTextCursor cursor = edit->textCursor();
                    QTextBlock block = edit->document()->findBlockByLineNumber(match.lineNumber - 1);
                    if (block.isValid()) {
                        cursor.setPosition(block.position() + match.matchStart);
                        cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor, match.matchLength);
                        edit->setTextCursor(cursor);
                        edit->ensureCursorVisible();
                    }
                }
            }
        });
    }
}

