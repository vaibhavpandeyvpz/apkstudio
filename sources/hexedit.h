#ifndef HEXEDIT_H
#define HEXEDIT_H

#include <QWidget>
#include "qhexview.h"

class HexEdit : public QWidget
{
    Q_OBJECT
private:
    QString m_FilePath;
    QHexView *m_HexView;
public:
    explicit HexEdit(QWidget *parent = nullptr);
    QString filePath();
    void open(const QString &path);
    bool save();
};

#endif // HEXEDIT_H
