/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the Qt3Support module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef Q3GRIDLAYOUT_H
#define Q3GRIDLAYOUT_H

#include <QtGui/qboxlayout.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

QT_MODULE(Qt3SupportLight)

class Q3GridLayout : public QGridLayout
{
public:
    inline explicit Q3GridLayout(QWidget *parent)
        : QGridLayout(parent) { setMargin(0); setSpacing(0); }

    inline Q3GridLayout(QWidget *parent, int nRows, int nCols = 1, int margin = 0,
                        int spacing = -1, const char *name = 0)
        : QGridLayout(parent, nRows, nCols, margin, spacing, name) {}

    inline Q3GridLayout(int nRows, int nCols = 1, int spacing = -1, const char *name = 0)
        : QGridLayout(nRows, nCols, spacing, name) {}

    inline Q3GridLayout(QLayout *parentLayout, int nRows =1, int nCols = 1, int spacing = -1,
                        const char *name = 0)
        : QGridLayout(parentLayout, nRows, nCols, spacing, name) {}

private:
    Q_DISABLE_COPY(Q3GridLayout)
};

QT_END_NAMESPACE

QT_END_HEADER

#endif // Q3GRIDLAYOUT_H
