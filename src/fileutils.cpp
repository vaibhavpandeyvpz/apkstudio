#include <QDir>
#include <QDesktopServices>
#include <QFile>
#include <QProcess>
#include <QTextCodec>
#include <QTextStream>
#include <QUrl>
#include "include/fileutils.h"
#include "include/preferences.h"

APP_NAMESPACE_START

QString FileUtils::read(const QString &p)
{
    QString c;
    QFile file(p);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream s(&file);
        s.setCodec(QTextCodec::codecForMib(Preferences::get()->textEncoding()));
        while (!s.atEnd())
        {
            c.append(s.readLine());
            c.append("\n");
        }
        file.close();
    }
    return c;
}

bool FileUtils::rimraf(const QString &d)
{
    bool s = true;
    QDir dir(d);
    if (dir.exists())
    {
        QFileInfoList files = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
        if (!files.isEmpty())
        {
            foreach (QFileInfo fi, files)
            {
                if (fi.isDir())
                {
                    s = rimraf(fi.absoluteFilePath());
                }
                else
                {
                    s = QFile::remove(fi.absoluteFilePath());
                }
                if (!s)
                {
                    return false;
                }
            }
        }
        s = dir.rmdir(d);
    }
    return s;
}

/**
 * @brief From http://lynxline.com/show-in-finder-show-in-explorer/
 */
void FileUtils::show(const QString &p)
{
#ifdef Q_OS_WIN
    QStringList args;
    args << "/select," << QDir::toNativeSeparators(p);
    QProcess::startDetached("explorer", args);
#elif defined(Q_OS_MAC)
    QStringList args;
    args << "-e" << "tell application \"Finder\"";
    args << "-e" << "activate" << "-e";
    args << "select POSIX file \"" + p + "\"";
    args << "-e" << "end tell";
    QProcess::startDetached("osascript", args);
#else
    QDesktopServices::openUrl(QUrl("file:///" + QFileInfo(p).absolutePath()));
#endif
}

APP_NAMESPACE_END
