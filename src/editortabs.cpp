#include <QDesktopServices>
#include <QFileInfo>
#include <QInputDialog>
#include <QTabBar>
#include <QTextCodec>
#include <QTextStream>
#include "include/coder.h"
#include "include/coderhighlighter.h"
#include "include/constants.h"
#include "include/editortabs.h"
#include "include/fileutils.h"
#include "include/findreplace.h"
#include "include/preferences.h"
#include "include/qrc.h"
#include "include/runner.h"
#include "include/viewer.h"

APP_NAMESPACE_START

EditorTabs::EditorTabs(QWidget *parent)
    : QTabWidget(parent)
{
    _connections << connect(parent, SIGNAL(editCopy()), this, SLOT(onEditCopy()));
    _connections << connect(parent, SIGNAL(editCut()), this, SLOT(onEditCut()));
    _connections << connect(parent, SIGNAL(editFind()), this, SLOT(onEditFind()));
    _connections << connect(parent, SIGNAL(editGoto()), this, SLOT(onEditGoto()));
    _connections << connect(parent, SIGNAL(editPaste()), this, SLOT(onEditPaste()));
    _connections << connect(parent, SIGNAL(editRedo()), this, SLOT(onEditRedo()));
    _connections << connect(parent, SIGNAL(editReplace()), this, SLOT(onEditReplace()));
    _connections << connect(parent, SIGNAL(editUndo()), this, SLOT(onEditUndo()));
    _connections << connect(parent, SIGNAL(fileClose()), this, SLOT(onFileClose()));
    _connections << connect(parent, SIGNAL(fileCloseAll()), this, SLOT(onFileCloseAll()));
    _connections << connect(parent, SIGNAL(fileOpen(QString)), this, SLOT(onFileOpen(QString)));
    _connections << connect(parent, SIGNAL(fileSave()), this, SLOT(onFileSave()));
    _connections << connect(parent, SIGNAL(fileSaveAll()), this, SLOT(onFileSaveAll()));
    _connections << connect(this, &QTabWidget::tabCloseRequested, this, &EditorTabs::onTabCloseRequested);
    _connections << connect(tabBar(), &QTabBar::tabMoved, this, &EditorTabs::onTabMoved);
    _connections << connect(this, &EditorTabs::currentChanged, this, &EditorTabs::onCurrentChanged);
    _connections << connect(this, SIGNAL(fileChanged(QString)), parent, SLOT(onFileChanged(QString)));
    _connections << connect(this, SIGNAL(fileSaved(QString)), parent, SLOT(onFileSaved(QString)));
    setMovable(true);
    setTabsClosable(true);
}

void EditorTabs::onCurrentChanged(const int i)
{
    emit fileChanged(_files.key(i, QString()));
    if (i >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)) && _finder)
        {
            _finder->setEditor(c);
        }
    }
}

void EditorTabs::onEditCopy()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            c->copy();
        }
    }
}

void EditorTabs::onEditCut()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            c->cut();
        }
    }
}

void EditorTabs::onEditFind()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            if (_finder)
            {
                _finder->close();
            }
            _finder = new FindReplace(false, w);
            _finder->setEditor(c);
            _finder->show();
        }
    }
}

void EditorTabs::onEditGoto()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            bool ok;
            int r = QInputDialog::getInt(this, __("goto", "titles"), __("line_no", "forms"), 1, 1, c->document()->blockCount(), 1, &ok);
            if (ok)
            {
                c->setTextCursor(QTextCursor(c->document()->findBlockByLineNumber(r - 1)));
            }
        }
    }
}

void EditorTabs::onEditPaste()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)) && c->canPaste())
        {
            c->paste();
        }
    }
}

void EditorTabs::onEditRedo()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            c->redo();
        }
    }
}

void EditorTabs::onEditReplace()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            if (_finder)
            {
                _finder->close();
            }
            _finder = new FindReplace(true, w);
            _finder->setEditor(c);
            _finder->show();
        }
    }
}

void EditorTabs::onEditUndo()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        QWidget *w = widget(i);
        Coder *c;
        if (w && (c = dynamic_cast<Coder *>(w)))
        {
            c->undo();
        }
    }
}

void EditorTabs::onFileClose()
{
    onTabCloseRequested(currentIndex());
}

void EditorTabs::onFileCloseAll()
{
    int i;
    while ((i = currentIndex()) >= 0)
    {
        onTabCloseRequested(i);
    }
}

void EditorTabs::onFileOpen(const QString &p)
{
    int i;
    QWidget *w;
    if ((i = _files.value(p, -1)) >= 0)
    {
        w = widget(i);
    }
    else
    {
        QFileInfo fi(p);
        QString ext = fi.suffix();
        if (QString(EDITOR_EXT_CODER).contains(ext, Qt::CaseInsensitive))
        {
            Coder *c = new Coder(this);
            c->setPlainText(FileUtils::read(p));
            new CoderHighlighter(fi.suffix() + ".def", HIGHLIGHTER_THEME, c->document());
            w = c;
        }
        else if (QString(EDITOR_EXT_VIEWER).contains(ext, Qt::CaseInsensitive))
        {
            Viewer *v = new Viewer(this);
            v->setPixmap(QPixmap(p));
            v->zoomReset();
            w = v;
        }
        else
        {
            QDesktopServices::openUrl(QUrl(p));
            return;
        }
        _files.insert(p, i = addTab(w, _provider.icon(fi), fi.fileName()));
    }
    setCurrentIndex(i);
    setTabToolTip(i, p);
    w->setProperty(TAB_PROPERTY_PATH, p);
    w->setFocus();
    emit fileChanged(p);
}

void EditorTabs::onFileSave()
{
    int i;
    if ((i = currentIndex()) >= 0)
    {
        onFileSave(i);
    }
}

void EditorTabs::onFileSave(const int i)
{
    QWidget *w = widget(i);
    Coder *c;
    if (w && (c = dynamic_cast<Coder *>(w)))
    {
        QString p = w->property(TAB_PROPERTY_PATH).toString();
        QFileInfo fi(p);
        if (fi.exists() || fi.isFile())
        {
            QFile f(p);
            if (f.open(QIODevice::Text | QIODevice::Truncate | QIODevice::WriteOnly))
            {
                QTextStream s(&f);
                s.setCodec(QTextCodec::codecForMib(Preferences::get()->textEncoding()));
                s.setGenerateByteOrderMark(false);
                s << c->toPlainText();
                f.close();
            }
            emit fileSaved(p);
        }
    }
}

void EditorTabs::onFileSaveAll()
{
    for (int i = 0; i < tabBar()->count(); i++)
    {
        onFileSave(i);
    }
}

void EditorTabs::onTabCloseRequested(const int i)
{
    if (i >= 0)
    {
        QWidget *w = widget(i);
        QString p = w->property(TAB_PROPERTY_PATH).toString();
        _files.remove(p);
        removeTab(i);
    }
}

void EditorTabs::onTabMoved(const int from, const int to)
{
    QString f = _files.key(from);
    QString t = _files.key(to);
    _files.insert(f, to);
    _files.insert(t, from);
}

EditorTabs::~EditorTabs()
{
    Preferences::get()
            ->setSessionFiles(_files.keys())
            ->save();
    APP_CONNECTIONS_DISCONNECT
}

APP_NAMESPACE_END
