#include <QFile>
#include <QVBoxLayout>
#include <QHexView/model/buffer/qmemorybuffer.h>
#include "hexedit.h"

HexEdit::HexEdit(QWidget *parent)
    : QWidget(parent)
{
    auto layout = new QVBoxLayout();
    layout->addWidget(m_HexView = new QHexView(this));
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

QString HexEdit::filePath()
{
    return m_FilePath;
}

void HexEdit::open(const QString &path)
{
    auto document = QHexDocument::fromFile(path);
    m_HexView->setDocument(document);
    m_FilePath = path;
}

bool HexEdit::save()
{
    QFile file(m_FilePath);
    if (file.open(QFile::WriteOnly)) {
        m_HexView->hexDocument()->saveTo(&file);
        file.close();
        return true;
    }
    return false;
}
