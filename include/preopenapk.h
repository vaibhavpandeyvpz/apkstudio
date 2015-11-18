#ifndef PREOPENAPK_H
#define PREOPENAPK_H

#include <QCheckBox>
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
    QCheckBox *_resources;
    QCheckBox *_sources;
private Q_SLOTS:
    void onBrowseProject();
public:
    explicit PreOpenApk(const QString &apk, QWidget *parent);
public Q_SLOTS:
    void accept();
};

APP_NAMESPACE_END

#endif // PREOPENAPK_H
