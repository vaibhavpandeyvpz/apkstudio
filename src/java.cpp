#include "include/constants.h"
#include "include/java.h"
#include "include/preferences.h"

APP_NAMESPACE_START

Java* Java::_self = NULL;

Java::Java(QObject *parent)
#ifdef Q_OS_WIN
    : Process("java.exe", parent)
#else
    : Process("java", parent)
#endif
{
}

Process::Result Java::exec(const QStringList &a)
{
    QString heap("-Xmx%1m");
    heap = heap.arg(QString::number(Preferences::get()->javaHeap()));
    return Process::exec(QStringList(heap) << a);
}

Java *Java::get()
{
    if (!_self)
    {
        _self = new Java();
    }
    return _self;
}

QString Java::getVersion()
{
    Process::Result r = exec("-version");
    QRegularExpression rgx(REGEX_JAVA_VERSION);
    foreach (const QString &l, r.output)
    {
        QRegularExpressionMatch m = rgx.match(l);
        if (m.hasMatch())
        {
            QString v("%1.%2.%3 %2u%4");
            for (int i = 1; i <= 4; i++)
            {
                v = v.arg(m.captured(i));
            }
            return v;
        }
    }
    return QString();
}

APP_NAMESPACE_END
