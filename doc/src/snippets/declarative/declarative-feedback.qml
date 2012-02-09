/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the Qt Mobility Components.
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
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
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
        width: 60; height: 20
        radius:5
        Text {
            anchors.centerIn: parent
            text: "Play Theme: Basic Button"
        }
        ThemeEffect {
             id: myOtherThemeEffect
             effect: "BasicButton"
         }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                myOtherThemeEffect.play();
            }
        }
    }

    //Example 2: using ThemeEffect without declaring element

    import QtFeedback.ThemeEffect 5.0 as MyTheme

    Rectangle {
        width: 60; height: 20
        radius:5
        Text {
            anchors.centerIn: parent
            text: "Play Theme: Basic Button"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                MyTheme.effect = "BasicButton"
                MyTheme.play();
            }
        }
    }

    //Example 3: using ThemeEffect without declaring element and calling overloaded play function

    import QtFeedback.ThemeEffect 5.0 as MyTheme

    Rectangle {
        width: 60; height: 20
        radius:5
        Text {
            anchors.centerIn: parent
            text: "Play Theme: Basic Button"
        }
        MouseArea {
            anchors.fill: parent
            onClicked: {
                MyTheme.play(ThemeEffect.BasicButton;)
            }
        }
    }

    //![Theme]
}
