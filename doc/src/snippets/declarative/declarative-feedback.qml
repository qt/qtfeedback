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


import QtQuick 2.0

Rectangle {
    id: page
    width: 800
    height: 350
    color: "olive"

    //![File Effect]
    import QtFeedback 5.0

    FileEffect {
        id: myFileEffect
        loaded: false
        source: "file:///myfile.ivs"
    }

    MouseArea {
        onClicked: myFileEffect.start();
    }

    //![File Effect]

    //![Haptics Effect]

    import QtFeedback 5.0

    HapticsEffect {
        id: rumbleEffect
        attackIntensity: 0.0
        attackTime: 250
        intensity: 1.0
        duration: 100
        fadeTime: 250
        fadeIntensity: 0.0
    }
    MouseArea {
        onClicked: {
        rumbleEffect.start();  // plays a rumble effect
    }

    //![Haptics Effect]

    //![Theme]
    //Example 1: using ThemeEffect declaring element

        import QtFeedback 5.0

        Rectangle {
            width: 180; height: 20
            radius:5
            color: "lightgrey"
            Text {
                anchors.centerIn: parent
                text: "Play Theme: Press"
            }
            ThemeEffect {
                 id: myOtherThemeEffect
                 effect: "Press"
             }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    myOtherThemeEffect.play();
                }
            }
        }

        //Example 2: using ThemeEffect without declaring element

        import QtFeedback.ThemeEffect 5.0 as Effect

        Rectangle {
            width: 180; height: 20
            radius:5
            color: "lightgrey"
            Text {
                anchors.centerIn: parent
                text: "Play Theme: Press"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Effect.effect = "Press"
                    Effect.play();
                }
            }
        }

        //Example 3: using ThemeEffect without declaring element and calling overloaded play function

        import QtFeedback.ThemeEffect 5.0 as Effect

        Rectangle {
            width: 180; height: 20
            radius:5
            color: "lightgrey"
            Text {
                anchors.centerIn: parent
                text: "Play Theme: Press"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Effect.play(Effect.Press)
                }
            }
        }

    //![Theme]

    //! [Play the system theme button click effect]
        import QtFeedback.ThemeEffect 5.0 as Effect

        Rectangle {
            width: 180; height: 20
            radius:5
            color: "lightgrey"
            Text {
                anchors.centerIn: parent
                text: "Play Theme: Press"
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    Effect.play(Effect.Press)
                }
            }
        }
    //! [Play the system theme button click effect]

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
    if (rumble.state === Feedback.Stopped)
        console.log("The device has stopped rumbling.")
    //! [Query the state of a custom haptic effect]

    //! [Set the actuator which should play the custom effect]
    for (var i = 0; rumble.availableActuators[i]; i++) {
        if (rumble.availableActuators[i].name === "ExampleActuatorName") {
           rumble.actuator = rumble.availableActuators[i]
           }
    }
    //! [Set the actuator which should play the custom effect]
