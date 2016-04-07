/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qfeedbackactuator.h>
#include <qfeedbackeffect.h>

#include <QDebug>


void completeExample();

void completeExample()
{
//! [Play the system theme button click effect]
    QFeedbackEffect::playThemeEffect(QFeedbackEffect::Press);
//! [Play the system theme button click effect]

//! [Play the system theme bounce effect]
    QFeedbackEffect::playThemeEffect(QFeedbackEffect::DragStart);
//! [Play the system theme bounce effect]

//! [Define a custom haptic effect]
    QFeedbackHapticsEffect rumble;
    rumble.setAttackIntensity(0.0);
    rumble.setAttackTime(250);
    rumble.setIntensity(1.0);
    rumble.setDuration(1000);
    rumble.setFadeTime(250);
    rumble.setFadeIntensity(0.0);
//! [Define a custom haptic effect]

//! [Start playing a custom haptic effect]
    rumble.start();
//! [Start playing a custom haptic effect]

//! [Pause a custom haptic effect]
    rumble.pause();
//! [Pause a custom haptic effect]

//! [Stop playing a custom haptic effect]
    rumble.stop();
//! [Stop playing a custom haptic effect]

//! [Query the state of a custom haptic effect]
    if (rumble.state() == QFeedbackEffect::Stopped)
        qDebug() << "The device has stopped rumbling!";
//! [Query the state of a custom haptic effect]

//! [Set the actuator which should play the custom effect]
    QFeedbackActuator *actuator = 0; // default system actuator
    QList<QFeedbackActuator*> actuators = QFeedbackActuator::actuators();
    foreach (QFeedbackActuator* temp, actuators) {
        if (temp->name() == "ExampleActuatorName") {
            actuator = temp;
        }
    }
    rumble.setActuator(actuator);
//! [Set the actuator which should play the custom effect]

//! [Play a haptic effect from a file]
    QFeedbackFileEffect hapticTune;
    hapticTune.setSource(QUrl::fromLocalFile("mySavedRumble.ivt"));
    hapticTune.load();
    hapticTune.start();
//! [Play a haptic effect from a file]
}
