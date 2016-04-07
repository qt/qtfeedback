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

#include "qdeclarativefeedbackactuator_p.h"

/*!
    \qmltype Actuator
    \instantiates QFeedbackActuator
    \brief The Actuator element represents a feedback actuator.
    \ingroup qml-feedback-api

    The Actuator class maps directly to the QFeedbackActuator C++ class, and
    can be used with HapticsEffect elements.

    There are several predefined enumerations and constants provided in this object:

    1. Capability
    \list
    \li Envelope - Value specifying that the device can bound its intensity by an envelope.
    \li Period  - Value specifying that the device can play periodic effects.
    \endlist

    2. State
    \list
    \li Busy    - The actuator is busy.
    \li Ready   - The actuator is ready to play an effect.
    \li Unknown - The actuator is in an unknown state.
    \endlist

    \sa HapticsEffect, {QFeedbackActuator}
*/
QDeclarativeFeedbackActuator::QDeclarativeFeedbackActuator(QObject *parent)
    :QObject(parent)
{
    d = new QFeedbackActuator(this);
    connect(d, SIGNAL(enabledChanged()), this, SIGNAL(enabledChanged()));
}

QDeclarativeFeedbackActuator::QDeclarativeFeedbackActuator(QObject *parent, QFeedbackActuator* actuator)
    :QObject(parent)
{
    d = actuator;
    connect(d, SIGNAL(enabledChanged()), this, SIGNAL(enabledChanged()));
}

QFeedbackActuator* QDeclarativeFeedbackActuator::feedbackActuator() const
{
    return d;
}

/*!
    \qmlproperty int Actuator::actuatorId
    This property holds the id of the feedback actuator.
    This property is read only.
*/
int QDeclarativeFeedbackActuator::actuatorId() const
{
    return d->id();
}

/*!
    \qmlproperty bool Actuator::valid

    This property is true if the actuator is valid.
    This property is read only.
*/
bool QDeclarativeFeedbackActuator::isValid() const
{
    return d->isValid();
}
/*!
   \qmlproperty  string Actuator::name
    This property holds the name of the feedback actuator.
    This property is read only.
*/
QString QDeclarativeFeedbackActuator::name() const
{
    return d->name();
}

/*!
    \qmlproperty enumeration Actuator::state
    This property holds the state of the feedback actuator.
    This property is read only.
*/
QDeclarativeFeedbackActuator::State QDeclarativeFeedbackActuator::state() const
{
    return static_cast<State>(d->state());
}

/*!
    \qmlmethod bool Actuator::isCapabilitySupported(enumeration capability)
    Returns if the actuator supports the supplied \a capability, available capabilities are:
    \list
    \li Envelope - Value specifying that the device can bound its intensity by an Envelope.
    \li Period   - Value specifying that the device can play periodic effects.
    \endlist
*/
bool QDeclarativeFeedbackActuator::isCapabilitySupported(Capability capability) const
{
    return d->isCapabilitySupported(static_cast<QFeedbackActuator::Capability>(capability));
}
/*!
    \qmlproperty bool Actuator::enabled
    This property is true if the feedback actuator is enabled.
*/

bool QDeclarativeFeedbackActuator::isEnabled() const
{
    return d->isEnabled();
}
void QDeclarativeFeedbackActuator::setEnabled(bool v)
{
    d->setEnabled(v);
}
