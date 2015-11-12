#include <QIcon>
#include <QProgressBar>
#include <QVBoxLayout>
#include "include/qrc.h"
#include "include/pleasewait.h"

APP_NAMESPACE_START

PleaseWait::PleaseWait(QWidget *p)
    : Dialog(__("please_wait", "titles"), p), _finished(false)
{
    setMinimumSize(0, 0);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint & ~Qt::WindowMinMaxButtonsHint);
    setWindowModality(Qt::WindowModal);
    QProgressBar *pb = new QProgressBar(this);
    pb->setRange(0, 0);
    pb->setTextVisible(false);
    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(pb);
    setLayout(l);
    adjustSize();
}

void PleaseWait::closeEvent(QCloseEvent *e)
{
    if (!_finished)
    {
        e->ignore();
    }
}

void PleaseWait::finish()
{
    _finished = true;
    close();
}

void PleaseWait::keyPressEvent(QKeyEvent *e)
{
    if (e->key() != Qt::Key_Escape)
    {
        Dialog::keyPressEvent(e);
    }
}

APP_NAMESPACE_END
