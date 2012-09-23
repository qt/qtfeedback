/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Feedback.
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
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
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

#include "ui_hapticsplayer.h"

#include <qfeedbackactuator.h>
#include <qfeedbackeffect.h>

#ifndef HAPTICSPLAYER_H_
#define HAPTICSPLAYER_H_

class HapticsPlayer : public QWidget
{
    Q_OBJECT
public:
    HapticsPlayer();

private Q_SLOTS:
    void actuatorChanged();
    void enabledChanged(bool);
    void playPauseClicked();
    void durationChanged(int);
    void intensityChanged(int);

    void attackTimeChanged(int);
    void attackIntensityChanged(int);
    void fadeTimeChanged(int);
    void fadeIntensityChanged(int);

    void periodChanged(int value);
    void periodToggled(bool on);

    //High-level API
    void instantPlayClicked();

    //File API
    void browseClicked();
    void filePlayPauseClicked();

#ifdef Q_OS_SYMBIAN
    void tabChanged(int index);
#endif
protected:
    void timerEvent(QTimerEvent *);

private:
    QFeedbackActuator* currentActuator();
    Ui_HapticsPlayer ui;
    QFeedbackActuator* actuator;
    QFeedbackHapticsEffect effect;
    QFeedbackFileEffect fileEffect;
};

#endif

