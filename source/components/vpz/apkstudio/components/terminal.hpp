#ifndef VPZ_APKSTUDIO_COMPONENTS_TERMINAL_HPP
#define VPZ_APKSTUDIO_COMPONENTS_TERMINAL_HPP

#include <QTextEdit>

namespace VPZ {
namespace APKStudio {
namespace Components {

class Terminal : public QTextEdit
{
    Q_OBJECT
private:
    QString binary;
    QColor command;
    QColor output;
public:
    explicit Terminal(const QString &, QWidget *parent = 0);
public slots:
    void onCommandExecuted(const QStringList &, const QStringList &);
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_TERMINAL_HPP
