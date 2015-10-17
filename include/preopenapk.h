#ifndef PREOPENAPK_H
#define PREOPENAPK_H

#include <QComboBox>
#include <QLineEdit>
#include "dialog.h"

APP_NAMESPACE_START

class PreOpenApk : public Dialog
{
    Q_OBJECT
private:
    QLineEdit *_apk;
    QLineEdit *_project;
    QComboBox *_framework;
public:
    explicit PreOpenApk(const QString &apk, QWidget *parent);
public:
    inline QString apk() { return _apk->text(); }
    QString framework();
    inline QString project() { return _project->text(); }
};

APP_NAMESPACE_END

#endif // PREOPENAPK_H
