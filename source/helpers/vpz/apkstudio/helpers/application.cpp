#include "application.hpp"

namespace VPZ {
namespace APKStudio {
namespace Helpers {

#ifdef Q_QDOC
    Application::Application(int &argc, char **argv)
        : QApplication(argc, argv)
    {
    }
#else
    Application::Application(int &argc, char **argv, int flags)
        : QApplication(argc, argv, flags)
    {
    }
#endif

    Resources::Theme Application::theme()
    {
        QVariant theme = instance()->property("theme");
        Resources::Theme styles = theme.isNull() ? Resources::Theme() : theme.value<Resources::Theme>();
        if (!styles.isEmpty())
            return styles;
        QFile *xml = new QFile(QString(RESOURCE_PATH_THEME).append(Settings::theme()).append(".xml"));
        if (xml->exists() && xml->open(QIODevice::ReadOnly | QIODevice::Text)) {
            QXmlStreamReader reader(xml);
            while (!reader.atEnd() && !reader.hasError()) {
                QXmlStreamReader::TokenType type = reader.readNext();
                if (type == QXmlStreamReader::StartDocument)
                    continue;
                if (type == QXmlStreamReader::StartElement) {
                    QString tag = reader.name().toString();
                    if ((tag != "style") || (tag == "theme"))
                        continue;
                    QXmlStreamAttributes attributes = reader.attributes();
                    if (!attributes.hasAttribute("name"))
                        continue;
                    QString name = attributes.value("name").toString();
                    if (!attributes.hasAttribute("color"))
                        continue;
                    QString color = attributes.value("color").toString();
                    Resources::Style style;
                    style.color = color;
                    style.bold = (attributes.hasAttribute("bold") && (QString::compare(attributes.value("bold").toString(), "true", Qt::CaseInsensitive) == 0));
                    style.italic = (attributes.hasAttribute("italic") && (QString::compare(attributes.value("italic").toString(), "true", Qt::CaseInsensitive) == 0));
                    style.underline = (attributes.hasAttribute("underline") && (QString::compare(attributes.value("underline").toString(), "true", Qt::CaseInsensitive) == 0));
                    styles.insert(name, style);
                }
            }
            reader.clear();
            xml->close();
        }
        theme.setValue<Resources::Theme>(styles);
        instance()->setProperty("theme", theme);
        return styles;
    }

} // namespace Helpers
} // namespace APKStudio
} // namespace VPZ
