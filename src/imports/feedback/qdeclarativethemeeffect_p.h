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

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists for the convenience
// of Qt Feedback framework.  This header file may change from version
// to version without notice, or even be removed.
//
// We mean it.
//
//

#ifndef QDECLARATIVETHEMEEFFECT_P_H
#define QDECLARATIVETHEMEEFFECT_P_H

#include <QtQml/qqml.h>
#include <qfeedbackeffect.h>

QT_USE_NAMESPACE

// Wrapper for theme effects
class QDeclarativeThemeEffect : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool supported READ effectSupported)
    Q_PROPERTY(Effect effect READ effect WRITE setEffect NOTIFY effectChanged)

    Q_CLASSINFO("DefaultMethod", "play()")
    Q_CLASSINFO("OverloadedMethod", "play(Effect)")

    Q_ENUMS(Effect)

public:
    enum Effect {
        Undefined = QFeedbackEffect::Undefined,
        Press = QFeedbackEffect::Press,
        Release = QFeedbackEffect::Release,
        PressWeak = QFeedbackEffect::PressWeak,
        ReleaseWeak = QFeedbackEffect::ReleaseWeak,
        PressStrong = QFeedbackEffect::PressStrong,
        ReleaseStrong = QFeedbackEffect::ReleaseStrong,
        DragStart = QFeedbackEffect::DragStart,
        DragDropInZone = QFeedbackEffect::DragDropInZone,
        DragDropOutOfZone = QFeedbackEffect::DragDropOutOfZone,
        DragCrossBoundary = QFeedbackEffect::DragCrossBoundary,
        Appear = QFeedbackEffect::Appear,
        Disappear = QFeedbackEffect::Disappear,
        Move = QFeedbackEffect::Move,
        NumberOfEffects = QFeedbackEffect::NumberOfEffects,
        UserEffect = QFeedbackEffect::UserEffect
    };

    QDeclarativeThemeEffect(QObject *parent = 0);
    bool effectSupported();
    void setEffect(Effect effect);
    Effect effect() const;

public slots:
    void play();
    void play(Effect effect);

signals:
    void effectChanged();

public:
    Effect m_effect;
};

QML_DECLARE_TYPE(QDeclarativeThemeEffect)

#endif // QDECLARATIVETHEMEEFFECT_P_H
