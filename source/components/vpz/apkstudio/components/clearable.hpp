#ifndef VPZ_APKSTUDIO_COMPONENTS_CLEARABLE_HPP
#define VPZ_APKSTUDIO_COMPONENTS_CLEARABLE_HPP

#include <QKeyEvent>
#include <QLineEdit>
#include <QStyle>
#include <QToolButton>
#include <QValidator>
#include "resources/embedded.hpp"

namespace VPZ {
namespace APKStudio {
namespace Components {

class Clearable : public QLineEdit
{
    Q_OBJECT
private:
    QList<QMetaObject::Connection> connections;
    QToolButton *empty;
private slots:
    void onTextChanged(const QString &);
protected:
    void resizeEvent(QResizeEvent *);
public:
    Clearable(QWidget * = 0);
    ~Clearable();
};

} // namespace Components
} // namespace APKStudio
} // namespace VPZ

#endif // VPZ_APKSTUDIO_COMPONENTS_CLEARABLE_HPP
