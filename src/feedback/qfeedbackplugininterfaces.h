/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtFeedback module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QFEEDBACKPLUGIN_H
#define QFEEDBACKPLUGIN_H

#include <qfeedbackactuator.h>
#include <qfeedbackeffect.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class Q_FEEDBACK_EXPORT QFeedbackInterface
{
public:
    enum PluginPriority {
        PluginLowPriority,
        PluginNormalPriority,
        PluginHighPriority
    };

protected:
    static void reportError(const QFeedbackEffect *, QFeedbackEffect::ErrorType);
};

class Q_FEEDBACK_EXPORT QFeedbackHapticsInterface : public QFeedbackInterface
{
public:
    //going with enums allow more flexibility without breaking BC
    enum EffectProperty {
        Duration,
        Intensity,
        AttackTime,
        AttackIntensity,
        FadeTime,
        FadeIntensity,
        Period //optional
    };

    enum ActuatorProperty {
        Name,
        State,
        Enabled
    };

    //static members for actuators management
    virtual QList<QFeedbackActuator*> actuators() = 0;
    virtual ~QFeedbackHapticsInterface() {}

    virtual PluginPriority pluginPriority() = 0;

    //for actuator handling
    virtual void setActuatorProperty(const QFeedbackActuator &, ActuatorProperty, const QVariant &) = 0;
    virtual QVariant actuatorProperty(const QFeedbackActuator &, ActuatorProperty) = 0;
    virtual bool isActuatorCapabilitySupported(const QFeedbackActuator &, QFeedbackActuator::Capability) = 0;
    
    //effects
    virtual void updateEffectProperty(const QFeedbackHapticsEffect *, EffectProperty) = 0;
    virtual void setEffectState(const QFeedbackHapticsEffect *, QFeedbackEffect::State) = 0;
    virtual QFeedbackEffect::State effectState(const QFeedbackHapticsEffect *) = 0;

    static QFeedbackHapticsInterface *instance();

protected:
    //utility function for the backends
    QFeedbackActuator* createFeedbackActuator(QObject* parent, int id);
};

class QFeedbackThemeInterface : public QFeedbackInterface
{
public:
    virtual ~QFeedbackThemeInterface() {}
    virtual PluginPriority pluginPriority() = 0;
    virtual bool play(QFeedbackEffect::Effect) = 0;
    static QFeedbackThemeInterface *instance();
};

class Q_FEEDBACK_EXPORT QFeedbackFileInterface : public QFeedbackInterface
{
public:
    virtual ~QFeedbackFileInterface() {}
    virtual void setLoaded(QFeedbackFileEffect*, bool) = 0;
    virtual void setEffectState(QFeedbackFileEffect *, QFeedbackEffect::State) = 0;
    virtual QFeedbackEffect::State effectState(const QFeedbackFileEffect *) = 0;
    virtual int effectDuration(const QFeedbackFileEffect*) = 0;
    virtual QStringList supportedMimeTypes() = 0;

    static QFeedbackFileInterface *instance();

protected:
    static void reportLoadFinished(QFeedbackFileEffect*, bool success);
};

Q_DECLARE_INTERFACE(QFeedbackHapticsInterface, "com.nokia.qt.QFeedbackHapticsInterface/1.0")
Q_DECLARE_INTERFACE(QFeedbackThemeInterface, "com.nokia.qt.QFeedbackThemeInterface/1.0")
Q_DECLARE_INTERFACE(QFeedbackFileInterface, "com.nokia.qt.QFeedbackFileInterface/1.0")

QT_END_NAMESPACE
QT_END_HEADER

#endif // QFEEDBACKPLUGININTERFACES_H
