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

#ifndef QFEEDBACKACTUATOR_H
#define QFEEDBACKACTUATOR_H

#include "qfeedbackglobal.h"
#include <QtCore/QObject>

QT_BEGIN_HEADER
QT_BEGIN_NAMESPACE

class QFeedbackEffect;

class Q_FEEDBACK_EXPORT QFeedbackActuator : public QObject
{
    Q_OBJECT

    Q_ENUMS(Capability)
    Q_ENUMS(State)

    Q_PROPERTY(int id READ id)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QFeedbackActuator::State state READ state)
    Q_PROPERTY(bool valid READ isValid)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    enum Capability {
        Envelope,
        Period
    };

    enum State {
        Busy,
        Ready,
        Unknown
    };

    explicit QFeedbackActuator(QObject *parent = Q_NULLPTR);

    int id() const;
    bool isValid() const;

    QString name() const;
    State state() const;

    Q_INVOKABLE bool isCapabilitySupported(Capability) const;

    bool isEnabled() const;
    void setEnabled(bool);

    static QList<QFeedbackActuator*> actuators();
    bool operator==(const QFeedbackActuator&) const;

Q_SIGNALS:
    void enabledChanged();

private:
    QFeedbackActuator(QObject *parent, int id);
    friend class QFeedbackHapticsInterface;
    int m_id;
};

QT_END_NAMESPACE
QT_END_HEADER

#endif // QFEEDBACKACTUATOR_H
