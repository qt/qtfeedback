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

#ifndef QFEEDBACK_MMK_H
#define QFEEDBACK_MMK_H

#include <QtCore/QHash>

#include <qfeedbackplugininterfaces.h>

#include <qsoundeffect.h>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QFeedbackMediaObject;

class QFeedbackMMK : public QObject, public QFeedbackFileInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtFeedbackPlugin" FILE "mmk.json")
    Q_INTERFACES(QFeedbackFileInterface)

public:
    QFeedbackMMK();
    virtual ~QFeedbackMMK();

    virtual void setLoaded(QFeedbackFileEffect*, bool);
    virtual void setEffectState(QFeedbackFileEffect *, QFeedbackEffect::State);
    virtual QFeedbackEffect::State effectState(const QFeedbackFileEffect *);
    virtual int effectDuration(const QFeedbackFileEffect*);
    virtual QStringList supportedMimeTypes();
private Q_SLOTS:
    void soundEffectStatusChanged();
    void soundEffectPlayingChanged();

private:
    struct FeedbackInfo {
        FeedbackInfo() : soundEffect(0), loaded(false), playing(false) {}
        QSoundEffect* soundEffect;
        bool loaded;
        bool playing;
    };

    QHash<const QFeedbackFileEffect*, FeedbackInfo> mEffects;
    QHash<const QSoundEffect*, QFeedbackFileEffect*> mEffectMap;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif // QFEEDBACK_MMK_H
