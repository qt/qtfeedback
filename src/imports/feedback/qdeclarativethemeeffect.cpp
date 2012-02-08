/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
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
    m_effect(QDeclarativeThemeEffect::Undefined)
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

    \o Effect.Undefined - Undefined feedback. No feedback is given.
    \o Effect.Press - Feedback for when the screen is pressed.
    \o Effect.Release - Feedback for touch release.
    \o Effect.PressWeak - A weak feedback for press.
    \o Effect.ReleaseWeak - A weak feedback for release.
    \o Effect.PressStrong - A strong feedback for press.
    \o Effect.ReleaseStrong - A strong feedback for release.
    \o Effect.PressAndHold - Feedback for long press.
    \o Effect.DragStart - Feedback for when dragging starts.
    \o Effect.DragDropInZone - Feedback for when dragging ends and touch is released inside a drop zone.
    \o Effect.DragDropOutOfZone - Feedback for when dragging ends and touch is released outside a drop zone.
    \o Effect.DragCrossBoundary - Feedback for when crossing a boundary while dragging.
    \o Effect.Popup - Feedback for when a popup item is shown.
    \o Effect.PopupClose - Feedback for when a popup item is closed.
    \o Effect.Move - Feedback for dragging on screen.
  \endlist

  \sa QFeedbackEffect::Effect
*/
void QDeclarativeThemeEffect::setEffect(QDeclarativeThemeEffect::Effect effect)
{
    if (m_effect != effect) {
        m_effect = effect;
        emit effectChanged();
    }
}

QDeclarativeThemeEffect::Effect QDeclarativeThemeEffect::effect() const
{
    return m_effect;
}

/*!
    \qmlmethod ThemeEffect::play()

    Call this to play the themed effect.
*/
void QDeclarativeThemeEffect::play()
{
    QFeedbackEffect::playThemeEffect(static_cast<QFeedbackEffect::Effect>(m_effect));
}

/*!
    \qmlmethod ThemeEffect::play(Effect)

    Call this to play the themed effect passed as parameter.

*/
void QDeclarativeThemeEffect::play(Effect effect)
{
    QFeedbackEffect::playThemeEffect(static_cast<QFeedbackEffect::Effect>(effect));
}
