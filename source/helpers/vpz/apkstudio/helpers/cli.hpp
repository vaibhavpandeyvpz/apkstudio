#ifndef VPZ_APKSTUDIO_HELPERS_CLI_HPP
#define VPZ_APKSTUDIO_HELPERS_CLI_HPP

#include <QObject>
#include <QProcess>
#include <QRegularExpression>

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class CLI : public QObject
{
    Q_OBJECT
protected:
    QString binary;
public:
    explicit CLI(const QString &, QObject *parent = 0);
    virtual QStringList execute(const QStringList &, const QString & = QString()) const;
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_CLI_HPP
