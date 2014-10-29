#ifndef VPZ_APKSTUDIO_WINDOWS_DIALOG_HPP
#define VPZ_APKSTUDIO_WINDOWS_DIALOG_HPP

#include <QDialog>

namespace VPZ {
namespace APKStudio {
namespace Windows {

class Dialog : public QDialog
{
    Q_OBJECT
protected:
    QList<QMetaObject::Connection> connections;
public:
    explicit Dialog(QWidget * = 0);
    ~Dialog();
};

} // namespace Windows
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_WINDOWS_DIALOG_HPP
