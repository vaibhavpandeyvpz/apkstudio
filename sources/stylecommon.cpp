/*
The MIT License (MIT)

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

#ifdef _WIN32

#ifdef NTDDI_VERSION
#undef NTDDI_VERSION
#endif

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#define NTDDI_VERSION NTDDI_VISTA
#define _WIN32_WINNT _WIN32_WINNT_VISTA

#include <windows.h>
#include <shellapi.h>

#include "stylecommon.h"

QPixmap StyleCommon::winStandardPixmap(QStyle::StandardPixmap standardPixmap)
{
    QPixmap pixmap;

    HICON hicon = nullptr;

    LPCWSTR icon_handle_xp = nullptr;
    SHSTOCKICONID icon_handle_vista = SIID_INVALID;

    switch (standardPixmap)
    {
    case QStyle::SP_MessageBoxInformation:
    {
        icon_handle_xp = IDI_INFORMATION;
        icon_handle_vista = SIID_INFO;
        break;
    }
    case QStyle::SP_MessageBoxWarning:
    {
        icon_handle_xp = IDI_WARNING;
        icon_handle_vista = SIID_WARNING;
        break;
    }
    case QStyle::SP_MessageBoxCritical:
    {
        icon_handle_xp = IDI_ERROR;
        icon_handle_vista = SIID_ERROR;
        break;
    }
    case QStyle::SP_MessageBoxQuestion:
    {
        icon_handle_xp = IDI_QUESTION;
        icon_handle_vista = SIID_HELP;
        break;
    }
    default:
        break;
    }

    typedef HRESULT(STDAPICALLTYPE *tSHGetStockIconInfo)(SHSTOCKICONID siid, UINT uFlags, SHSTOCKICONINFO *psii);
    tSHGetStockIconInfo pSHGetStockIconInfo = tSHGetStockIconInfo(QLibrary::resolve("shell32", "SHGetStockIconInfo"));

    if (pSHGetStockIconInfo)
    {
        if (icon_handle_vista != SIID_INVALID)
        {
            SHSTOCKICONINFO sii;
            memset(&sii, 0, sizeof(SHSTOCKICONINFO));
            sii.cbSize = sizeof(sii);

            if (SUCCEEDED(pSHGetStockIconInfo(icon_handle_vista, SHGSI_ICON | SHGSI_LARGEICON, &sii)))
            {
                hicon = sii.hIcon;
            }
        }
    }
    else
    {
        if (icon_handle_xp)
        {
            hicon = LoadIconW(nullptr, icon_handle_xp);
        }
    }

    if (hicon)
    {
#ifdef QT_VERSION_QT5
        pixmap = QtWin::fromHICON(hicon);
#endif
#ifdef QT_VERSION_QT6
        pixmap = QPixmap::fromImage(QImage::fromHICON(hicon));
#endif
        DestroyIcon(hicon);
    }

    return pixmap;
}

#endif
