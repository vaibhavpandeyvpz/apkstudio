#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QLabel>
#include <QStatusBar>
#include "macros.h"

APP_NAMESPACE_START

class StatusBar : public QStatusBar
{
    Q_OBJECT
private:
    APP_CONNECTIONS_LIST
    QLabel *_message;
private Q_SLOTS:
    void onMessageChanged(const QString &text);
public:
    explicit StatusBar(QWidget *parent);
    ~StatusBar();
};

class StatusBarSeparator : public QFrame
{
public:
    explicit StatusBarSeparator(QWidget *parent = 0);
};

APP_NAMESPACE_END

#endif // STATUSBAR_H
