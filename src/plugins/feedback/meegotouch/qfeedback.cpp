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

#include "qfeedback.h"
#include "qfeedbackeffect.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QtPlugin>

#include <meegotouch/MFeedback>

// TODO Use a style property based enum to play the correct feedback
//enum MeegoTouchFeedback
//{
//    // MWidgetStyle
//    widgetPressFeedback,
//    widgetReleaseFeedback,
//    widgetCancelFeedback,
//    // MSliderStyle
//    sliderMoveFeedback,
//    // MTextEditStyle
//    textEditPressBoundaryFeedback,
//    textEditReleaseBoundaryFeedback,
//    textEditPressWordFeedback,
//    textEditReleaseWordFeedback,
//    textEditChangeSelectionFeedback
//};

static QString convertToMeegoTouch(QFeedbackEffect::ThemeEffect effect)
{
    switch (effect) {
    case QFeedbackEffect::Press:
    case QFeedbackEffect::Release:
    case QFeedbackEffect::PressWeak:
    case QFeedbackEffect::ReleaseWeak:
    case QFeedbackEffect::PressStrong:
    case QFeedbackEffect::ReleaseStrong:
    case QFeedbackEffect::DragStart:
    case QFeedbackEffect::DragDropInZone:
    case QFeedbackEffect::DragDropOutOfZone:
    case QFeedbackEffect::DragCrossBoundary:
    case QFeedbackEffect::Appear:
    case QFeedbackEffect::Disappear:
    case QFeedbackEffect::Move:
        return MFeedback::Press;
    default:
        return QString();
    }
}

QFeedbackMeegoTouch::QFeedbackMeegoTouch(QObject *parent) :
    QObject(parent),
    QFeedbackThemeInterface()
{
}

bool QFeedbackMeegoTouch::play(QFeedbackEffect::Effect effect)
{
    const QString &feedbackString = convertToMeegoTouch(effect);
    if (feedbackString.isEmpty())
        return false;

    MFeedback::play(feedbackString);
    return true;
}

QFeedbackInterface::PluginPriority QFeedbackMeegoTouch::pluginPriority()
{
    return QFeedbackInterface::PluginLowPriority;
}

