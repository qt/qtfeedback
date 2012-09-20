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

#include "hapticsplayer.h"

#include <QtCore/qmetaobject.h>

#include <QtGui/QFileDialog>
#include <QDebug>

static const char ENUM_THEME_EFFECT[] = "ThemeEffect";
static const char ENUM_ANIMATION_STATE[] = "State";

HapticsPlayer::HapticsPlayer() : actuator(0)
{
    ui.setupUi(this);

#if defined(Q_WS_MAEMO_5)
    // maemo5 style problem: title of groupboxes is rendered badly if there isn't enough space
    // that is, the sizehint of the title area is Preferred rather than Minimum.
    // to fix that, we manually tweak some spacers.
    ui.verticalSpacer_2->changeSize(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.verticalSpacer_3->changeSize(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.verticalSpacer_4->changeSize(20, 30, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.verticalSpacer_5->changeSize(20, 30, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.verticalSpacer_6->changeSize(20, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    ui.verticalSpacer_7->changeSize(20, 30, QSizePolicy::Expanding, QSizePolicy::Fixed);
#endif

    connect(ui.actuators, SIGNAL(currentIndexChanged(int)), SLOT(actuatorChanged()));
    connect(ui.enabled, SIGNAL(toggled(bool)), SLOT(enabledChanged(bool)));
    connect(ui.playPause, SIGNAL(pressed()), SLOT(playPauseClicked()));
    connect(ui.stop, SIGNAL(pressed()), &effect, SLOT(stop()));
    connect(ui.duration, SIGNAL(valueChanged(int)), SLOT(durationChanged(int)));
    connect(ui.intensity, SIGNAL(valueChanged(int)), SLOT(intensityChanged(int)));

    //for the envelope
    connect(ui.attackTime, SIGNAL(valueChanged(int)), SLOT(attackTimeChanged(int)));
    connect(ui.attackIntensity, SIGNAL(valueChanged(int)), SLOT(attackIntensityChanged(int)));
    connect(ui.fadeTime, SIGNAL(valueChanged(int)), SLOT(fadeTimeChanged(int)));
    connect(ui.fadeIntensity, SIGNAL(valueChanged(int)), SLOT(fadeIntensityChanged(int)));

    //for the period
    connect(ui.grpPeriod, SIGNAL(toggled(bool)), SLOT(periodToggled(bool)));
    connect(ui.period, SIGNAL(valueChanged(int)), SLOT(periodChanged(int)));

    connect(ui.instantPlay, SIGNAL(pressed()), SLOT(instantPlayClicked()));

    //file API
    connect(ui.browse, SIGNAL(pressed()), SLOT(browseClicked()));
    connect(ui.filePlayPause, SIGNAL(pressed()), SLOT(filePlayPauseClicked()));
    connect(ui.fileStop, SIGNAL(pressed()), &fileEffect, SLOT(stop()));
    // if pausing a playing effect is not supported then stop playback
    connect(&fileEffect, SIGNAL(error(QFeedbackEffect::ErrorType)), &fileEffect, SLOT(stop()));

    foreach (QFeedbackActuator *dev, QFeedbackActuator::actuators()) {
        ui.actuators->addItem(dev->name());
    }
    if (QFeedbackActuator::actuators().count() > 0)
        ui.actuators->setCurrentIndex(0);

    //adding the instant effects
    const QMetaObject &mo = QFeedbackEffect::staticMetaObject;
    const QMetaEnum &me = mo.enumerator(mo.indexOfEnumerator(ENUM_THEME_EFFECT));
    Q_ASSERT(me.keyCount());
    for (int i = 0 ; i < me.keyCount(); ++i) {
        ui.instantEffect->addItem(me.key(i));
    }

    //initialization
    durationChanged(effect.duration());
    intensityChanged(ui.intensity->value());
    attackTimeChanged(ui.attackTime->value());
    attackIntensityChanged(ui.attackIntensity->value());
    fadeTimeChanged(ui.fadeTime->value());
    fadeIntensityChanged(ui.fadeIntensity->value());

    ui.tabWidget->setTabEnabled(1, QFeedbackEffect::supportsThemeEffect());
    ui.tabWidget->setTabEnabled(2, !QFeedbackFileEffect::supportedMimeTypes().isEmpty());
#ifdef Q_OS_SYMBIAN
    // Due to focus handling problems when using tabwidget in Qt/s60 with old non-touch-screen devices
    // we have to handle focus explicitly here, this might get fixed at some point
    connect(ui.tabWidget,SIGNAL(currentChanged(int)),this,SLOT(tabChanged(int)));
    // force initial focus to a button on the first tab
    ui.tabWidget->setCurrentIndex(0);
    ui.playPause->setFocus();
#endif
    //that is a hackish way of updating the info concerning the effects
    startTimer(50);
}

QFeedbackActuator* HapticsPlayer::currentActuator()
{
    QList<QFeedbackActuator*> devs = QFeedbackActuator::actuators();
    int index = ui.actuators->currentIndex();
    if (index == -1 || devs.count() == 0 || index > devs.count()) {
        if (!actuator) {
            actuator = new QFeedbackActuator(this);
        }
        return actuator;
    }
    return devs.at(index);
}

void HapticsPlayer::actuatorChanged()
{
    QFeedbackActuator* dev = currentActuator();
    if (dev) {
        enabledChanged(dev->isEnabled());
        effect.setActuator(dev);
    }
}

#ifdef Q_OS_SYMBIAN
void HapticsPlayer::tabChanged(int index)
{
    switch (index) {
        case 0:
           ui.playPause->setFocus();
           break;
        case 1:
           ui.instantPlay->setFocus();
           break;
        case 2:
           ui.browse->setFocus();
           break;
    }
}
#endif

void HapticsPlayer::enabledChanged(bool on)
{
    if (!on)
        effect.stop();
    QFeedbackActuator* dev = currentActuator();
    if (dev) {
        dev->setEnabled(on);
        ui.enabled->setChecked(dev->isEnabled());

        if (dev->isEnabled() && (dev->isCapabilitySupported(QFeedbackActuator::Envelope))) {
            ui.envelope->setEnabled(true);
            ui.envelope->show();
        } else {
            ui.envelope->setEnabled(true);
            ui.envelope->hide();
        }
        if (dev->isEnabled() && (dev->isCapabilitySupported(QFeedbackActuator::Period))) {
            ui.grpPeriod->setEnabled(true);
            ui.grpPeriod->show();
        } else {
            ui.grpPeriod->setEnabled(false);
            ui.grpPeriod->hide();
        }
    }
#ifdef Q_OS_SYMBIAN
    ui.playPause->setFocus();
#endif
}

void HapticsPlayer::playPauseClicked()
{
    if (effect.state() == QFeedbackEffect::Running) {
        effect.pause();
    } else {
        effect.start();
    }
}

void HapticsPlayer::durationChanged(int duration)
{
    effect.setDuration(duration);
    ui.attackTime->setMaximum(duration);
    ui.fadeTime->setMaximum(duration);
    attackTimeChanged(ui.attackTime->value());
}

void HapticsPlayer::intensityChanged(int value)
{
    effect.setIntensity(qreal(value) / ui.intensity->maximum());
    ui.lblIntensity->setText(QString::number(effect.intensity()));
}

void HapticsPlayer::timerEvent(QTimerEvent *e)
{
    //update the display for effect
    {
        QFeedbackEffect::State newState = effect.state();
        const QMetaObject *mo = effect.metaObject();
        ui.effectState->setText(mo->enumerator(mo->indexOfEnumerator(ENUM_ANIMATION_STATE)).key(newState));
        ui.stop->setEnabled(newState != QFeedbackEffect::Stopped);
        if (effect.state() == QFeedbackEffect::Paused || effect.state() == QFeedbackEffect::Stopped)
            ui.playPause->setText(tr("Play"));
        else
            ui.playPause->setText(tr("Pause"));
    }

    //update the display for effect
    {
        QFeedbackEffect::State newState = fileEffect.state();
        const QMetaObject *mo = fileEffect.metaObject();
        ui.fileEffectState->setText(mo->enumerator(mo->indexOfEnumerator(ENUM_ANIMATION_STATE)).key(newState));
        ui.fileStop->setEnabled(newState != QFeedbackEffect::Stopped);
        ui.filePlayPause->setEnabled(fileEffect.isLoaded());
        ui.browse->setEnabled(newState == QFeedbackEffect::Stopped);
        ui.fileStatus->setText( fileEffect.isLoaded() ? QString::fromLatin1("%1 : %2 ms").arg(tr("Loaded")).arg(fileEffect.duration()) : tr("Not Loaded") );
    }
    QWidget::timerEvent(e);
}

void HapticsPlayer::attackTimeChanged(int attackTime)
{
    effect.setAttackTime(attackTime);
    //let's check the boundaries
    if (attackTime + ui.fadeTime->value() > ui.duration->value())
        ui.fadeTime->setValue(ui.duration->value() - attackTime);
}

void HapticsPlayer::attackIntensityChanged(int attackIntensity)
{
    effect.setAttackIntensity(qreal(attackIntensity) / ui.attackIntensity->maximum());
    ui.lblAttackIntensity->setText(QString::number(effect.attackIntensity()));
}

void HapticsPlayer::fadeTimeChanged(int fadeTime)
{
    effect.setFadeTime(fadeTime);
    //let's check the boundaries
    if (fadeTime + ui.attackTime->value() > ui.duration->value())
        ui.attackTime->setValue(ui.duration->value() - fadeTime);
}

void HapticsPlayer::fadeIntensityChanged(int fadeIntensity)
{
    effect.setFadeIntensity(qreal(fadeIntensity) / ui.fadeIntensity->maximum());
    ui.lblFadeIntensity->setText(QString::number(effect.fadeIntensity()));
}

void HapticsPlayer::periodToggled(bool on)
{
    effect.setPeriod(on ? ui.period->value() : 0);
}

void HapticsPlayer::periodChanged(int value)
{
    effect.setPeriod(value);
}

void HapticsPlayer::instantPlayClicked()
{
    const QMetaObject &mo = QFeedbackEffect::staticMetaObject;
    const QMetaEnum &me = mo.enumerator(mo.indexOfEnumerator(ENUM_THEME_EFFECT));
    QFeedbackEffect::playThemeEffect(QFeedbackEffect::ThemeEffect(me.keyToValue(ui.instantEffect->currentText().toLatin1())));
}

void HapticsPlayer::browseClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Feedback file"));
    if (!filename.isEmpty()) {
        ui.filename->setText(QDir::toNativeSeparators(filename));
        fileEffect.setSource(QUrl::fromLocalFile(filename));
        fileEffect.load();
    }
}

void HapticsPlayer::filePlayPauseClicked()
{
    if (fileEffect.state() == QFeedbackEffect::Running)
        fileEffect.pause();
    else
        fileEffect.start();
}

#include "moc_hapticsplayer.cpp"
