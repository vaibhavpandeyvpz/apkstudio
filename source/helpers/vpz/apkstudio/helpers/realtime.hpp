#ifndef VPZ_APKSTUDIO_HELPERS_REALTIME_HPP
#define VPZ_APKSTUDIO_HELPERS_REALTIME_HPP

#include <QIODevice>
#include <QMutex>
#include <QTextStream>
#include <QThread>
#include <QProcess>

namespace VPZ {
namespace APKStudio {
namespace Helpers {

class Realtime : public QThread
{
    Q_OBJECT
private:
    QStringList arguments;
    QString binary;
    QList<QMetaObject::Connection> connections;
    bool finished;
    QMutex mutex;
protected:
    void run();
public:
    explicit Realtime(const QString &, QObject * = 0);
    void start(const QStringList &);
    void stop();
    ~Realtime();
signals:
    void lineRead(QString);
    void stateChanged(bool);
};

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_HELPERS_REALTIME_HPP
