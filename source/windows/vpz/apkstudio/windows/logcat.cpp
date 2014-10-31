#include "logcat.hpp"

using namespace VPZ::APKStudio::Helpers;

namespace VPZ {
namespace APKStudio {
namespace Windows {

Logcat::Logcat(const QString &device, QWidget *parent) :
    Dialog(parent), debug(true), error(true), info(true), device(device), regex(QRegularExpression(REGEX_LOGCAT)), verbose(true), warning(true)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(2, 2, 2, 2);
    layout->setSpacing(0);
    setLayout(layout);
    setWindowIcon(icon("resource_monitor"));
    setWindowTitle(translate("title_window").arg(device));
    createReceiver();
    createToolbar();
    createTree();
}

void Logcat::closeEvent(QCloseEvent *event)
{
    Dialog::closeEvent(event);
}

void Logcat::createReceiver()
{
#ifdef Q_OS_WIN
    receiver = new Helpers::Realtime(Settings::binary("adb.exe"), this);
#else
    receiver = new Helpers::Realtime(Settings::binary("adb"), this);
#endif
    connections.append(connect(receiver, SIGNAL(lineRead(QString)), this, SLOT(onLineRead(QString))));
    connections.append(connect(receiver, SIGNAL(stateChanged(bool)), this, SLOT(onStateChanged(bool))));
}

void Logcat::createToolbar()
{
    QToolBar *tool_bar = new QToolBar(this);
    QAction *clear = new QAction(icon("bin_empty"), translate("label_clear"), tool_bar);
    QAction *debug = new QAction(icon("info_debug"), translate("label_debug"), tool_bar);
    QAction *error = new QAction(icon("info_error"), translate("label_error"), tool_bar);
    QAction *info = new QAction(icon("info_success"), translate("label_info"), tool_bar);
    QAction *open = new QAction(icon("folder_open"), translate("label_open"), tool_bar);
    QAction *save = new QAction(icon("disk"), translate("label_save"), tool_bar);
    QAction *scroll = new QAction(icon("arrow_skip_bottom"), translate("label_scroll"), tool_bar);
    QAction *start = new QAction(icon("control_play"), translate("label_start"), tool_bar);
    QAction *stop = new QAction(icon("control_stop"), translate("label_stop"), tool_bar);
    QAction *verbose = new QAction(icon("info_verbose"), translate("label_verbose"), tool_bar);
    QAction *warning = new QAction(icon("info_warning"), translate("label_warning"), tool_bar);
    debug->setCheckable(true);
    debug->setChecked(true);
    error->setCheckable(true);
    error->setChecked(true);
    info->setCheckable(true);
    info->setChecked(true);
    scroll->setCheckable(true);
    scroll->setChecked(true);
    stop->setEnabled(false);
    verbose->setCheckable(true);
    verbose->setChecked(true);
    warning->setCheckable(true);
    warning->setChecked(true);
    tool_bar->addAction(start);
    tool_bar->addAction(stop);
    tool_bar->addSeparator();
    tool_bar->addAction(open);
    tool_bar->addAction(clear);
    tool_bar->addSeparator();
    tool_bar->addAction(verbose);
    tool_bar->addAction(debug);
    tool_bar->addAction(info);
    tool_bar->addAction(warning);
    tool_bar->addAction(error);
    tool_bar->addSeparator();
    tool_bar->addAction(save);
    tool_bar->addSeparator();
    tool_bar->addAction(scroll);
    tool_bar->setAcceptDrops(false);
    tool_bar->setMovable(false);
    connections.append(connect(clear, &QAction::triggered, [ this ] () {
        if (this->tree->model()->hasChildren())
            this->tree->model()->removeRows(0, this->tree->model()->rowCount());
    }));
    connections.append(connect(debug, &QAction::toggled, [ this ] (const bool checked) {
        this->debug = checked;
    }));
    connections.append(connect(error, &QAction::toggled, [ this ] (const bool checked) {
        this->error = checked;
    }));
    connections.append(connect(info, &QAction::toggled, [ this ] (const bool checked) {
        this->info = checked;
    }));
    connections.append(connect(open, &QAction::triggered, this, &Logcat::onOpen));
    connections.append(connect(save, &QAction::triggered, this, &Logcat::onSave));
    connections.append(connect(scroll, &QAction::toggled, [ this ] (const bool checked) {
        this->scroll = checked;
    }));
    connections.append(connect(start, &QAction::triggered, [ this ] () {
        QStringList clear("-s");
        clear << this->device;
        clear << "logcat";
        clear << "-c";
        ADB::instance()->execute(clear);
        QStringList receive("-s");
        receive << this->device;
        receive << "logcat";
        receive << "-v";
        receive << "threadtime";
        this->createReceiver();
        this->receiver->start(receive);
    }));
    connections.append(connect(stop, &QAction::triggered, [ this ] () {
        this->receiver->stop();
    }));
    connections.append(connect(verbose, &QAction::toggled, [ this ] (const bool checked) {
        this->verbose = checked;
    }));
    connections.append(connect(warning, &QAction::toggled, [ this ] (const bool checked) {
        this->warning = checked;
    }));
    connections.append(connect(this, &Logcat::stateChanged, [ debug, error, info, open, save, start, stop, verbose, warning ] (const bool running) {
        debug->setEnabled(!running);
        error->setEnabled(!running);
        info->setEnabled(!running);
        open->setEnabled(!running);
        save->setEnabled(!running);
        start->setEnabled(!running);
        stop->setEnabled(running);
        verbose->setEnabled(!running);
        warning->setEnabled(!running);
    }));
    layout()->addWidget(tool_bar);
}

void Logcat::createTree()
{
    QShortcut *shortcut = new QShortcut(QKeySequence::Copy, this);
    tree = new QTreeWidget(this);
    tree->setContextMenuPolicy(Qt::CustomContextMenu);
    tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tree->setRootIsDecorated(false);
    tree->setSelectionBehavior(QAbstractItemView::SelectRows);
    tree->setSelectionMode(QAbstractItemView::MultiSelection);
    tree->setSortingEnabled(true);
    tree->setUniformRowHeights(true);
    tree->sortByColumn(1, Qt::DescendingOrder);
    QStringList labels;
    labels << translate("header_priority");
    labels << translate("header_time");
    labels << translate("header_pid");
    labels << translate("header_tid");
    labels << translate("header_tag");
    labels << translate("header_message");
    connections.append(connect(shortcut, &QShortcut::activated, this, &Logcat::onCopy));
    layout()->addWidget(tree);
    tree->setHeaderLabels(labels);
    tree->setColumnWidth(0, 48);
    tree->setColumnWidth(1, 96);
    tree->setColumnWidth(2, 32);
    tree->setColumnWidth(3, 32);
    tree->setColumnWidth(4, 128);
}

void Logcat::onCopy()
{
    if (tree->model()->rowCount() < 1)
        return;
    QStringList lines;
    QModelIndex root = tree->rootIndex();
    int rows = tree->model()->rowCount(root);
    for (int row = 0; row < rows; ++row) {
        QModelIndex line = tree->model()->index(row, 0, root);
        lines << qvariant_cast<QString>(tree->model()->data(line, ROLE_TEXT));
    }
    QClipboard *clipboard = Application::clipboard();
    clipboard->setText(lines.join("\n"));
}

void Logcat::onLineRead(const QString &line)
{
    if (line.isEmpty())
        return;
    QRegularExpressionMatch matcher = regex.match(line);
    if (!matcher.hasMatch())
        return;
    QColor color;
    char priority = matcher.captured("priority").at(0).toLatin1();
    switch (priority) {
    case 'D': {
        if (!debug)
            return;
        color = QColor("#0072BC");
        break;
    }
    case 'E': {
        if (!error)
            return;
        color = QColor("#ED1C24");
        break;
    }
    case 'I': {
        if (!info)
            return;
        color = QColor("#39B54A");
        break;
    }
    case 'W': {
        if (!warning)
            return;
        color = QColor("#ABA000");
        break;
    }
    case 'V':
        if (!verbose)
            return;
    case 'A':
    case 'F':
    default:
        color = QColor("#000000");
        break;
    }
    QTreeWidgetItem *item = new QTreeWidgetItem();
    item->setData(0, ROLE_TEXT, line);
    item->setData(0, Qt::TextAlignmentRole, Qt::AlignCenter);
    item->setData(1, Qt::TextAlignmentRole, Qt::AlignCenter);
    item->setData(2, Qt::TextAlignmentRole, Qt::AlignCenter);
    item->setData(3, Qt::TextAlignmentRole, Qt::AlignCenter);
    item->setForeground(0, color);
    item->setForeground(1, color);
    item->setForeground(2, color);
    item->setForeground(3, color);
    item->setForeground(4, color);
    item->setForeground(5, color);
    item->setText(0, matcher.captured("priority").at(0));
    item->setText(1, matcher.captured("time"));
    item->setText(2, matcher.captured("pid"));
    item->setText(3, matcher.captured("tid"));
    item->setText(4, matcher.captured("tag"));
    item->setText(5, matcher.captured("message"));
    while (tree->model()->rowCount() >= 1000)
        tree->model()->removeRow(0);
    tree->addTopLevelItem(item);
    if (scroll)
        tree->scrollToBottom();
}

void Logcat::onOpen()
{
    QFileDialog dialog(this, translate("title_open"), Settings::previousDirectory(), "Logcat output (*.logcat)");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    if (dialog.exec() != QFileDialog::Accepted)
        return;
    QStringList files = dialog.selectedFiles();
    if (files.isEmpty())
        return;
    Settings::previousDirectory(dialog.directory().absolutePath());
    QFile file(files.first());
    if (!file.open(QIODevice::Text | QIODevice::ReadOnly))
        return;
    if (tree->model()->hasChildren())
        tree->model()->removeRows(0, tree->model()->rowCount());
    QTextStream stream(&file);
    QString line;
    do {
        line = stream.readLine();
        if (line.isEmpty())
            continue;
        onLineRead(line);
    } while (!line.isNull());
    file.close();
}

void Logcat::onSave()
{
    if (tree->model()->rowCount() < 1)
        return;
    QString name = QString(Settings::previousDirectory());
    name.append('/');
    name.append(device);
    name.append('_');
    name.append(Format::timestamp(QDateTime::currentDateTime(), FORMAT_TIMESTAMP_FILE));
    QFileDialog dialog(this, translate("title_save"), name, "Logcat output (*.logcat)");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::AnyFile);
    if (dialog.exec() != QFileDialog::Accepted)
        return;
    QStringList files = dialog.selectedFiles();
    if (files.isEmpty())
        return;
    Settings::previousDirectory(dialog.directory().absolutePath());
    QFile file(files.first());
    if (file.exists())
        file.remove();
    if (!file.open(QIODevice::Text | QIODevice::WriteOnly))
        return;
    QTextStream stream(&file);
    QModelIndex root = tree->rootIndex();
    int rows = tree->model()->rowCount(root);
    for (int row = 0; row < rows; ++row) {
        QModelIndex line = tree->model()->index(row, 0, root);
        stream << qvariant_cast<QString>(tree->model()->data(line, ROLE_TEXT)) << endl;
    }
    file.close();
}

void Logcat::onStateChanged(const bool running)
{
    emit stateChanged(running);
}

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ
