/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Mobility Components.
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
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qfeedback_symbian.h"
#include <QtCore/QVariant>
#include <QtCore/QtPlugin>
#include <QtGui/QApplication>

// This is included if we have themed effect support

#include <touchfeedback.h>

MTouchFeedback *QFeedbackSymbian::touchInstance()
{
    static MTouchFeedback *ret = 0;
    if (!ret) {
        QT_TRAP_THROWING(
            ret = MTouchFeedback::Instance();
            if (!ret)
                ret = MTouchFeedback::CreateInstanceL();
        )
    }
    return ret;
}

static TTouchLogicalFeedback convertToSymbian(QFeedbackEffect::Effect effect)
{
    switch (effect) {
    case QFeedbackEffect::Press:
    case QFeedbackEffect::Release:
    case QFeedbackEffect::PressWeak:
    case QFeedbackEffect::ReleaseWeak:
    case QFeedbackEffect::PressStrong:
    case QFeedbackEffect::ReleaseStrong:
    case QFeedbackEffect::PressAndHold:
    case QFeedbackEffect::DragStart:
    case QFeedbackEffect::DragDropInZone:
    case QFeedbackEffect::DragDropOutOfZone:
    case QFeedbackEffect::DragCrossBoundary:
    case QFeedbackEffect::Popup:
    case QFeedbackEffect::PopupClose:
    case QFeedbackEffect::Move:
        return ETouchFeedbackBasic;
    default:
        return ETouchFeedbackNone;
    }
}

bool QFeedbackSymbian::play(QFeedbackEffect::Effect effect)
{
    TInt err = KErrNone;
    TRAP(err, touchInstance()->InstantFeedback(convertToSymbian(effect)));
    return err == KErrNone;
}
