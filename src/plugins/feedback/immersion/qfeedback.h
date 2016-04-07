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

#ifndef QFEEDBACK_IMMERSION_H
#define QFEEDBACK_IMMERSION_H

#include <QtCore/QList>
#include <QtCore/QVector>
#include <QtCore/QHash>
#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QTimer>

#include <qfeedbackplugininterfaces.h>

#include <ImmVibe.h>

QT_BEGIN_HEADER
QT_USE_NAMESPACE

class QFeedbackImmersion : public QObject, public QFeedbackHapticsInterface, public QFeedbackFileInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtFeedbackPlugin" FILE "immersion.json")

    Q_INTERFACES(QTM_NAMESPACE::QFeedbackHapticsInterface)
    Q_INTERFACES(QTM_NAMESPACE::QFeedbackFileInterface)

public:
    QFeedbackImmersion();
    virtual ~QFeedbackImmersion();

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

private:
    VibeInt32 handleForActuator(const QFeedbackActuator &actuator);
    VibeInt32 handleForActuator(int actId);
    static VibeInt32 convertedDuration(int duration);
    QFeedbackEffect::State updateImmState(const QFeedbackEffect *effect, VibeInt32 effectHandle, VibeInt32 state);

    void killTimerForHandle(VibeInt32 handle);
    void startTimerForHandle(VibeInt32 handle, const QFeedbackHapticsEffect* effect);
    void startTimerForHandle(VibeInt32 handle, QFeedbackFileEffect* effect);

    QMutex mutex;
    QVector<VibeInt32> actuatorHandles;
    QList<QFeedbackActuator*> actuatorList;
    QHash<const QFeedbackEffect*, VibeInt32> effectHandles;
    QHash<VibeInt32, QTimer*> effectTimers;

    struct FileContent {
        FileContent() : refCount(0) { }
        FileContent(const QByteArray &arr) : ba(arr), refCount(1) { }
        const VibeUInt8 *constData() const {return reinterpret_cast<const VibeUInt8 *>(ba.constData()); }

        QByteArray ba;
        int refCount;
    };
    QHash<QString, FileContent> fileData;
};

QT_END_HEADER

#endif // QFEEDBACK_IMMERSION_H
