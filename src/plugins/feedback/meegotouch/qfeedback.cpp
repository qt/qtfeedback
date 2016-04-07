/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtFeedback module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
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

