/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <qfeedbackactuator.h>
#include "qfeedbacktestplugin.h"
#include <QtCore/QtPlugin>
#include <QtCore/QDebug>
#include <QtCore/QStringList>
#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QVariant>
#include <QDebug>

QFeedbackTestPlugin::QFeedbackTestPlugin()
    : QObject(qApp), mHapticState(QFeedbackEffect::Stopped), mFileState(QFeedbackEffect::Stopped)
{
    actuators_ << createFeedbackActuator(this, 0) << createFeedbackActuator(this, 1);
}

QFeedbackTestPlugin::~QFeedbackTestPlugin()
{
}

QFeedbackInterface::PluginPriority QFeedbackTestPlugin::pluginPriority()
{
    return PluginHighPriority; // to make sure we get used
}

QList<QFeedbackActuator*> QFeedbackTestPlugin::actuators()
{
    return actuators_;
}

void QFeedbackTestPlugin::setActuatorProperty(const QFeedbackActuator &actuator, ActuatorProperty prop, const QVariant &value)
{
    Q_UNUSED(actuator)
    Q_UNUSED(prop)
    Q_UNUSED(value)
}

QVariant QFeedbackTestPlugin::actuatorProperty(const QFeedbackActuator &actuator, ActuatorProperty prop)
{
    Q_UNUSED(actuator)

    switch (prop) {
        case Name:
        if (actuator.id() == 0)
            return QString(QLatin1String("test plugin"));
        else
            return QString(QLatin1String("5555"));

        case State:
            return static_cast<int>(QFeedbackActuator::Unknown);

        case Enabled:
            return false;
        default:
            break;
    }

    return QVariant();
}

bool QFeedbackTestPlugin::isActuatorCapabilitySupported(const QFeedbackActuator &, QFeedbackActuator::Capability cap)
{
    switch (cap) {
        case QFeedbackActuator::Envelope:
        case QFeedbackActuator::Period:
            return true;
        default:
            break;
    }

    return false;
}

QTimer* QFeedbackTestPlugin::ensureTimer(const QFeedbackHapticsEffect* effect)
{
    // Yes, this is slow
    QTimer *t = mHapticEffects.key(effect);
    if (!t) {
        t = new QTimer();
        t->setSingleShot(true);
        t->setInterval(effect->duration());
        connect(t, SIGNAL(timeout()), this, SLOT(timerExpired()));
        mHapticEffects.insert(t, effect);
    }
    return t;
}


void QFeedbackTestPlugin::updateEffectProperty(const QFeedbackHapticsEffect *effect, EffectProperty ep)
{
    if (ep == QFeedbackHapticsInterface::Duration) {
        QTimer* t = ensureTimer(effect);
        t->setInterval(effect->duration());
    }
}

void QFeedbackTestPlugin::setEffectState(const QFeedbackHapticsEffect *effect, QFeedbackEffect::State state)
{
    Q_UNUSED(effect)
    if (mHapticState != state) {
        mHapticState = state;
        QTimer* t = ensureTimer(effect);
        if (mHapticState == QFeedbackEffect::Running) {
            t->start();
        } else if (mHapticState == QFeedbackEffect::Stopped) {
            t->stop();
        } else if (mHapticState == QFeedbackEffect::Paused) {
            // In theory should set the duration to the remainder...
            t->stop();
        }
    }
}

QFeedbackEffect::State QFeedbackTestPlugin::effectState(const QFeedbackHapticsEffect *effect)
{
    Q_UNUSED(effect)
    return mHapticState;
}

void QFeedbackTestPlugin::timerExpired()
{
    mHapticState = QFeedbackEffect::Stopped;
    // Emit the stateChanged signal
    const QFeedbackHapticsEffect* effect = mHapticEffects.value(static_cast<QTimer*>(sender()));
    if (effect) {
        QMetaObject::invokeMethod(const_cast<QFeedbackHapticsEffect*>(effect), "stateChanged");
    }
}



void QFeedbackTestPlugin::setLoaded(QFeedbackFileEffect *effect, bool load)
{
    if (effect->source() == QUrl("load")) {
        // Succeed the load
        if (load) {
            mFileState = QFeedbackEffect::Loading;
            reportLoadFinished(effect, true); // not strictly true
        } else
            mFileState = QFeedbackEffect::Stopped;
    } else {
        // Fail the load
        if (load)
            reportLoadFinished(effect, false);
    }
}

void QFeedbackTestPlugin::setEffectState(QFeedbackFileEffect *effect, QFeedbackEffect::State state)
{
    Q_UNUSED(effect)
    if (effect->source() == QUrl("load")) // we only change state for good effects
        mFileState = state;
}

QFeedbackEffect::State QFeedbackTestPlugin::effectState(const QFeedbackFileEffect *effect)
{
    Q_UNUSED(effect)
    return mFileState;
}

int QFeedbackTestPlugin::effectDuration(const QFeedbackFileEffect *effect)
{
    Q_UNUSED(effect)
    return 5678;
}

QStringList QFeedbackTestPlugin::supportedMimeTypes()
{
    return QStringList() << "x-test/this is a test";
}

bool QFeedbackTestPlugin::play(QFeedbackEffect::Effect effect)
{
    if (effect == QFeedbackEffect::Press)
        return true;
    else {
        reportError(0, QFeedbackEffect::UnknownError);
        return false;
    }
}
