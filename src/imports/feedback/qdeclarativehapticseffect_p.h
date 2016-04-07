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

#ifndef QDECLARATIVEHAPTICSEFFECT_P_H
#define QDECLARATIVEHAPTICSEFFECT_P_H

#include "qdeclarativefeedbackeffect_p.h"
#include "qdeclarativefeedbackactuator_p.h"

QT_USE_NAMESPACE

class QDeclarativeHapticsEffect : public QDeclarativeFeedbackEffect
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<QDeclarativeFeedbackActuator> availableActuators READ availableActuators)
    Q_PROPERTY(qreal intensity READ intensity WRITE setIntensity NOTIFY intensityChanged)
    Q_PROPERTY(int attackTime READ attackTime WRITE setAttackTime NOTIFY attackTimeChanged)
    Q_PROPERTY(qreal attackIntensity READ attackIntensity WRITE setAttackIntensity NOTIFY attackIntensityChanged)
    Q_PROPERTY(int fadeTime READ fadeTime WRITE setFadeTime NOTIFY fadeTimeChanged)
    Q_PROPERTY(qreal fadeIntensity READ fadeIntensity WRITE setFadeIntensity NOTIFY fadeIntensityChanged)
    Q_PROPERTY(int period READ period WRITE setPeriod NOTIFY periodChanged)
    Q_PROPERTY(QDeclarativeFeedbackActuator* actuator READ actuator WRITE setActuator NOTIFY actuatorChanged)

public:
    explicit QDeclarativeHapticsEffect(QObject *parent = 0);

    void setDuration(int msecs);
    int duration() const;
    void setIntensity(qreal intensity);
    qreal intensity() const;
    //the envelope
    void setAttackTime(int msecs);
    int attackTime() const;
    void setAttackIntensity(qreal intensity);
    qreal attackIntensity() const;
    void setFadeTime(int msecs);
    int fadeTime() const;
    void setFadeIntensity(qreal intensity);
    qreal fadeIntensity() const;
    void setPeriod(int msecs);
    int period() const;
    void setActuator(QDeclarativeFeedbackActuator *actuator);
    QDeclarativeFeedbackActuator* actuator() const;
    QQmlListProperty<QDeclarativeFeedbackActuator> availableActuators();
    static int actuator_count(QQmlListProperty<QDeclarativeFeedbackActuator> *prop);
    static QDeclarativeFeedbackActuator *actuator_at(QQmlListProperty<QDeclarativeFeedbackActuator> *prop, int index);

signals:
    void intensityChanged();
    void attackTimeChanged();
    void attackIntensityChanged();
    void fadeTimeChanged();
    void fadeIntensityChanged();
    void periodChanged();
    void actuatorChanged();

private:
    QFeedbackHapticsEffect* d;
    QList<QDeclarativeFeedbackActuator*> m_actuators;
    QDeclarativeFeedbackActuator* m_actuator;
};

QML_DECLARE_TYPE(QDeclarativeHapticsEffect)

#endif // QDECLARATIVEHAPTICSEFFECT_P_H
