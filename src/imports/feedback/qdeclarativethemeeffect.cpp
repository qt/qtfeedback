/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtFeedback module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qdeclarativethemeeffect_p.h"
/*!
    \qmltype ThemeEffect
    \brief The ThemeEffect element represents a themed feedback effect.
    \ingroup qml-feedback-api

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

    \li Effect.Undefined - Undefined feedback. No feedback is given.
    \li Effect.Press - Feedback for when the screen is pressed.
    \li Effect.Release - Feedback for touch release.
    \li Effect.PressWeak - A weak feedback for press.
    \li Effect.ReleaseWeak - A weak feedback for release.
    \li Effect.PressStrong - A strong feedback for press.
    \li Effect.ReleaseStrong - A strong feedback for release.
    \li Effect.DragStart - Feedback for when dragging starts.
    \li Effect.DragDropInZone - Feedback for when dragging ends and touch is released inside a drop zone.
    \li Effect.DragDropOutOfZone - Feedback for when dragging ends and touch is released outside a drop zone.
    \li Effect.DragCrossBoundary - Feedback for when crossing a boundary while dragging.
    \li Effect.Appear - Feedback for when an item is shown.
    \li Effect.Disappear - Feedback for when an item item is closed.
    \li Effect.Move - Feedback for dragging on screen.
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
