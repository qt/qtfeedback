/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtFeedback module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QFEEDBACKTESTPLUGIN_H
#define QFEEDBACKTESTPLUGIN_H


#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QHash>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QTimer>

#include <qfeedbackplugininterfaces.h>

QT_BEGIN_HEADER
QT_USE_NAMESPACE

class QFeedbackTestPlugin : public QObject, public QFeedbackHapticsInterface, public QFeedbackFileInterface, public QFeedbackThemeInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtFeedbackTestPlugin")
    Q_INTERFACES(QFeedbackHapticsInterface)
    Q_INTERFACES(QFeedbackFileInterface)
    Q_INTERFACES(QFeedbackThemeInterface)
public:
    QFeedbackTestPlugin();
    virtual ~QFeedbackTestPlugin();

    virtual PluginPriority pluginPriority();

    virtual QList<QFeedbackActuator*> actuators();

    //for actuator handling
    virtual void setActuatorProperty(const QFeedbackActuator &, ActuatorProperty, const QVariant &);
    virtual QVariant actuatorProperty(const QFeedbackActuator &, ActuatorProperty);
    virtual bool isActuatorCapabilitySupported(const QFeedbackActuator &, QFeedbackActuator::Capability);

    virtual void updateEffectProperty(const QFeedbackHapticsEffect *, EffectProperty);
    virtual void setEffectState(const QFeedbackHapticsEffect *, QFeedbackEffect::State);
    virtual QFeedbackEffect::State effectState(const QFeedbackHapticsEffect *);

    //for loading files
    virtual void setLoaded(QFeedbackFileEffect*, bool);
    virtual void setEffectState(QFeedbackFileEffect *, QFeedbackEffect::State);
    virtual QFeedbackEffect::State effectState(const QFeedbackFileEffect *);
    virtual int effectDuration(const QFeedbackFileEffect *);
    virtual QStringList supportedMimeTypes();

    // For themes
    virtual bool play(QFeedbackEffect::Effect);

private slots:
    void timerExpired();

private:
    QList<QFeedbackActuator*> actuators_;

    // Our hacky state
    QFeedbackEffect::State mHapticState;
    QFeedbackEffect::State mFileState;
    QMap<QTimer*, const QFeedbackHapticsEffect*> mHapticEffects;
    QTimer* ensureTimer(const QFeedbackHapticsEffect* effect);
};

QT_END_HEADER

#endif
