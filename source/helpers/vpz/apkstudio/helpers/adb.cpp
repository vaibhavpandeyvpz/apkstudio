#include "adb.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

ADB::ADB(const QString &executable, QObject *parent) :
    CLI(executable, parent)
{
}

QMap<QString, QString> ADB::properties(const QString &device) const
{
    QMap<QString, QString> properties;
    QStringList arguments;
    arguments << "-s";
    arguments << device;
    arguments << "shell";
    arguments << "getprop";
    QStringList output = execute(arguments);
    QRegularExpression regex = QRegularExpression(QString(REGEX_GETPROP));
    foreach (const QString &line, output) {
        if (line.startsWith('#'))
            continue;
        QRegularExpressionMatch matcher = regex.match(line);
        if (!matcher.hasMatch())
            continue;
        QString key = matcher.captured(QString("key"));
        QString value = matcher.captured(QString("value"));
        properties.insert(key.trimmed(), value.trimmed());
    }
    return properties;
}

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
