#include <QDir>
#include <QFile>
#include <QSize>
#include <QTextCodec>
#include "constants.h"
#include "preferences.h"

Preferences* Preferences::_self = nullptr;

Preferences::Preferences(QSettings *settings)
    : _settings(settings)
{
}

Preferences *Preferences::get()
{
    if (!_self)
    {
        _self = new Preferences(new QSettings(QSettings::IniFormat, QSettings::UserScope, APP_ORGANIZATION, APP_NAME));
    }
    return _self;
}

QVariant Preferences::get(const QString &k, const QVariant &f)
{
    return _settings->value(k, f);
}

void Preferences::save()
{
    _settings->sync();
}

Preferences *Preferences::set(const QString &k, const QVariant &v)
{
    _settings->setValue(k, v);
    return this;
}

/**
 * @brief Getters
 */
QString Preferences::binariesPath()
{
    return get(PREF_BIN_PATH).toString();
}

QByteArray Preferences::docksState()
{
    return get(PREF_DOCKS_STATE).toByteArray();
}

int Preferences::javaHeap()
{
    return get(PREF_JAVA_HEAP, PREF_DEFAULT_JAVA_HEAP).toInt();
}

QString Preferences::previousDir()
{
    QString d = get(PREF_PREVIOUS_DIR).toString();
    if (d.isEmpty() || !QDir(d).exists())
    {
        d = QDir::homePath();
    }
    return d;
}

QString Preferences::previousProject()
{
    return get(PREF_PREVIOUS_PROJECT).toString();
}

bool Preferences::showWhitespaces()
{
    return get(PREF_SHOW_WHITESPACES, false).toBool();
}

QString Preferences::signKey()
{
    return get(PREF_SIGN_KEY).toString();
}

QString Preferences::signKeyPass()
{
    return get(PREF_SIGN_KEY_PASS).toString();
}

QString Preferences::signKeystore()
{
    return get(PREF_SIGN_KEYSTORE).toString();
}

QString Preferences::signKeystorePass()
{
    return get(PREF_SIGN_KEYSTORE_PASS).toString();
}

int Preferences::tabStopWidth()
{
    return get(PREF_TAB_STOP_WIDTH, PREF_DEFAULT_TAB_STOP_WIDTH).toInt();
}

int Preferences::textEncoding()
{
    int e = get(PREF_TEXT_ENCODING, -1).toInt();
    return (e < 0) ? QTextCodec::codecForName(PREF_DEFAULT_TEXT_ENCODING)->mibEnum() : e;
}

bool Preferences::useSpacesForTabs()
{
    return get(PREF_SPACES_FOR_TABS, false).toBool();
}

bool Preferences::wasWindowMaximized()
{
    return get(PREF_WINDOW_MAXIMIZED).toBool();
}

QSize Preferences::windowSize()
{
    return get(PREF_WINDOW_SIZE).toSize();
}

/**
 * @brief Setters
 */
Preferences *Preferences::setBinariesPath(const QString &p)
{
    return set(PREF_BIN_PATH, p);
}

Preferences *Preferences::setDocksState(const QByteArray &s)
{
    return set(PREF_DOCKS_STATE, s);
}

Preferences *Preferences::setJavaHeap(const int mb)
{
    return set(PREF_JAVA_HEAP, mb);
}

Preferences *Preferences::setPreviousDir(const QString &d)
{
    return set(PREF_PREVIOUS_DIR, d);
}

Preferences *Preferences::setPreviousProject(const QString &p)
{
    return set(PREF_PREVIOUS_PROJECT, p);
}

Preferences *Preferences::setShowWhitespaces(const bool s)
{
    return set(PREF_SHOW_WHITESPACES, s);
}

Preferences *Preferences::setSignKey(const QString &n)
{
    return set(PREF_SIGN_KEY, n);
}

Preferences *Preferences::setSignKeyPass(const QString &p)
{
    return set(PREF_SIGN_KEY_PASS, p);
}

Preferences *Preferences::setSignKeystore(const QString &k)
{
    return set(PREF_SIGN_KEYSTORE, k);
}

Preferences *Preferences::setSignKeystorePass(const QString &p)
{
    return set(PREF_SIGN_KEYSTORE_PASS, p);
}

Preferences *Preferences::setTabStopWidth(const int w)
{
    return set(PREF_TAB_STOP_WIDTH, w);
}

Preferences *Preferences::setTextEncoding(const int c)
{
    return set(PREF_TEXT_ENCODING, c);
}

Preferences *Preferences::setUseSpacesForTabs(const bool u)
{
    return set(PREF_SPACES_FOR_TABS, u);
}

Preferences *Preferences::setWindowMaximized(bool m)
{
    return set(PREF_WINDOW_MAXIMIZED, m);
}

Preferences *Preferences::setWindowSize(const QSize &s)
{
    return set(PREF_WINDOW_SIZE, s);
}
