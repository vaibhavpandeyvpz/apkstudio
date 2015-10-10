#ifndef MACROS_H
#define MACROS_H

#define APP_NAMESPACE ApkStudio
#define APP_NAMESPACE_START namespace APP_NAMESPACE {
#define APP_NAMESPACE_END }
#define AS_CONNECTIONS_LIST QList<QMetaObject::Connection> _connections;
#define AS_CONNECTIONS_DISCONNECT for (QMetaObject::Connection c : _connections) { disconnect(c); }

#endif // MACROS_H
