/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtFeedback module of the Qt Toolkit.
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

#include "qdeclarativethemeeffect_p.h"
/*!
    \qmlclass ThemeEffect
    \brief The ThemeEffect element represents a themed feedback effect.
    \ingroup qml-feedback-api

    This element is part of the \bold{QtMobility.feedback 1.1} module.

    This element is used for playing feedback effects that follow the
    system theme.  The actual feedback might be haptic, audio or some other
    method.

    \snippet doc/src/snippets/declarative/declarative-feedback.qml Theme
*/
QDeclarativeThemeEffect::QDeclarativeThemeEffect(QObject *parent)
    : QObject(parent),
    m_effect(QDeclarativeThemeEffect::Press)
{
}

/*!
    \qmlproperty bool ThemeEffect::supported

    This property is true if the system supports themed feedback effects.
*/
bool QDeclarativeThemeEffect::effectSupported() {
    return QFeedbackEffect::supportsThemeEffect();
}

/*!
    \qmlproperty ThemeEffect ThemeEffect::effect

    This property holds the specific themed effect type to play.  It is one of:

    \o ThemeEffect.Press - Feedback for when the screen is pressed.
    \o ThemeEffect.Release - Feedback for touch release.
    \o ThemeEffect.PressWeak - A weak feedback for press.
    \o ThemeEffect.ReleaseWeak - A weak feedback for release.
    \o ThemeEffect.PressStrong - A strong feedback for press.
    \o ThemeEffect.ReleaseStrong - A strong feedback for release.
    \o ThemeEffect.PressAndHold - Feedback for long press.
    \o ThemeEffect.DragStart - Feedback for when dragging starts.
    \o ThemeEffect.DragDropInZone - Feedback for when dragging ends and touch is released inside a drop zone.
    \o ThemeEffect.DragDropOutOfZone - Feedback for when dragging ends and touch is released outside a drop zone.
    \o ThemeEffect.DragCrossBoundary - Feedback for when crossing a boundary while dragging.
    \o ThemeEffect.Popup - Feedback for when a popup item is shown.
    \o ThemeEffect.PopupClose - Feedback for when a popup item is closed.
    \o ThemeEffect.Move - Feedback for dragging on screen.
  \endlist

  \sa QFeedbackEffect::ThemeEffect
*/
void QDeclarativeThemeEffect::setEffect(QDeclarativeThemeEffect::ThemeEffect effect)
{
    if (m_effect != effect) {
        m_effect = effect;
        emit effectChanged();
    }
}

QDeclarativeThemeEffect::ThemeEffect QDeclarativeThemeEffect::effect() const
{
    return m_effect;
}

/*!
    \qmlmethod ThemeEffect::play()

    Call this to play the themed effect.
*/
void QDeclarativeThemeEffect::play()
{
    QFeedbackEffect::playThemeEffect(static_cast<QFeedbackEffect::ThemeEffect>(m_effect));
}

