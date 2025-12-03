/*
The MIT License (MIT)

Copyright © 2018, Juergen Skrotzky (https://github.com/Jorgen-VikingGod, JorgenVikingGod@gmail.com)
Copyright © 2018-2024 Antonio Dias (https://github.com/antonypro)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "darkstyle.h"
#include "stylecommon.h"

DarkStyle::DarkStyle() : DarkStyle(styleBase())
{
#ifdef Q_OS_WIN
    m_hash_pixmap_cache[SP_MessageBoxInformation] = StyleCommon::winStandardPixmap(SP_MessageBoxInformation);
    m_hash_pixmap_cache[SP_MessageBoxWarning] = StyleCommon::winStandardPixmap(SP_MessageBoxWarning);
    m_hash_pixmap_cache[SP_MessageBoxCritical] = StyleCommon::winStandardPixmap(SP_MessageBoxCritical);
    m_hash_pixmap_cache[SP_MessageBoxQuestion] = StyleCommon::winStandardPixmap(SP_MessageBoxQuestion);
#endif
}

DarkStyle::DarkStyle(QStyle *style) : QProxyStyle(style)
{

}

DarkStyle::~DarkStyle()
{

}

QStyle *DarkStyle::styleBase() const
{
    QStyle *base = QStyleFactory::create(QStringLiteral("Fusion"));
    return base;
}

QIcon DarkStyle::standardIcon(StandardPixmap standardPixmap, const QStyleOption *option, const QWidget *widget) const
{
#ifdef Q_OS_WIN
    switch (standardPixmap)
    {
    case SP_MessageBoxInformation:
    case SP_MessageBoxWarning:
    case SP_MessageBoxCritical:
    case SP_MessageBoxQuestion:
    {
        QPixmap pixmap = m_hash_pixmap_cache.value(standardPixmap, QPixmap());

        if (!pixmap.isNull())
            return QIcon(pixmap);

        break;
    }
    default:
        break;
    }
#endif

    return QProxyStyle::standardIcon(standardPixmap, option, widget);
}

void DarkStyle::polish(QPalette &palette)
{
    palette.setColor(QPalette::Window, QColor(53, 53, 53));
    palette.setColor(QPalette::WindowText, QColor(255, 255, 255));
    palette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
    palette.setColor(QPalette::Base, QColor(42, 42, 42));
    palette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    palette.setColor(QPalette::ToolTipBase, QColor(255, 255, 255));
    palette.setColor(QPalette::ToolTipText, QColor(255, 255, 255));
    palette.setColor(QPalette::Text, QColor(255, 255, 255));
    palette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
    palette.setColor(QPalette::Dark, QColor(35, 35, 35));
    palette.setColor(QPalette::Shadow, QColor(20, 20, 20));
    palette.setColor(QPalette::Button, QColor(53, 53, 53));
    palette.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    palette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
    palette.setColor(QPalette::BrightText, QColor(255, 0, 0));
    palette.setColor(QPalette::Link, QColor(42, 130, 218));
    palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    palette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
    palette.setColor(QPalette::HighlightedText, QColor(255, 255, 255));
    palette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));
}

void DarkStyle::polish(QApplication *app)
{
    if (!app)
        return;

    QFont defaultFont = app->font();
    defaultFont.setPointSize(defaultFont.pointSize() + 2);
    app->setFont(defaultFont);

    QFile file(QStringLiteral(":/styles/dark.qss"));

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QString style_sheet = QLatin1String(file.readAll());
        app->setStyleSheet(style_sheet);
        file.close();
    }
}

void DarkStyle::unpolish(QApplication *app)
{
    if (!app)
        return;

    QFont defaultFont = app->font();
    defaultFont.setPointSize(defaultFont.pointSize() - 2);
    app->setFont(defaultFont);
}

QStyle *DarkStyle::baseStyle() const
{
    return styleBase();
}
