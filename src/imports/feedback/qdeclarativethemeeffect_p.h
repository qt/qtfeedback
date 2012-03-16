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
