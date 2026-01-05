#ifndef FINDINFILESDIALOG_H
#define FINDINFILESDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QProgressBar>
#include <QSplitter>
#include <QTextEdit>
#include <QTreeWidget>

class MainWindow;

struct SearchMatch {
    QString filePath;
    int lineNumber;
    QString lineText;
    int matchStart;
    int matchLength;
    
    bool operator==(const SearchMatch &other) const {
        return filePath == other.filePath && lineNumber == other.lineNumber;
    }
};

Q_DECLARE_METATYPE(SearchMatch)

class FindInFilesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit FindInFilesDialog(MainWindow *parent = nullptr);
    void setSearchRoot(const QString &rootPath);
private:
    MainWindow *m_MainWindow;
    QLineEdit *m_EditSearch;
    QCheckBox *m_CheckCase;
    QCheckBox *m_CheckWhole;
    QCheckBox *m_CheckRegexp;
    QListWidget *m_ResultsList;
    QTextEdit *m_PreviewText;
    QLabel *m_LabelStatus;
    QProgressBar *m_ProgressBar;
    QSplitter *m_Splitter;
    QString m_SearchRoot;
    QList<SearchMatch> m_Matches;
    
    void buildUI();
    void performSearch();
    void updateResults();
    void onResultClicked(QListWidgetItem *item);
    void scanDirectory(const QString &dirPath, const QString &searchTerm, 
                      bool caseSensitive, bool wholeWords, bool useRegexp);
    bool isTextFile(const QString &filePath);
    QStringList getTextFileExtensions();
    void highlightMatchInPreview(const QString &text, int matchStart, int matchLength);
private slots:
    void handleSearch();
    void handleResultSelectionChanged();
};

#endif // FINDINFILESDIALOG_H

