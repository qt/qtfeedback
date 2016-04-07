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

#ifndef QDECLARATIVEFEEDBACKACTUATOR_P_H
#define QDECLARATIVEFEEDBACKACTUATOR_P_H

#include <QtQml/qqml.h>
#include "qfeedbackactuator.h"

QT_USE_NAMESPACE

class QDeclarativeFeedbackActuator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int actuatorId READ actuatorId)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(State state READ state)
    Q_PROPERTY(bool valid READ isValid)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

    Q_ENUMS(Capability)
    Q_ENUMS(State)

public:
    enum Capability {
        Envelope = QFeedbackActuator::Envelope,
        Period = QFeedbackActuator::Period
    };

    enum State {
        Busy = QFeedbackActuator::Busy,
        Ready = QFeedbackActuator::Ready,
        Unknown = QFeedbackActuator::Unknown
    };

    explicit QDeclarativeFeedbackActuator(QObject *parent = 0);
    explicit QDeclarativeFeedbackActuator(QObject *parent, QFeedbackActuator* actuator);
    QFeedbackActuator* feedbackActuator() const;
    int actuatorId() const;
    bool isValid() const;
    QString name() const;
    State state() const;
    Q_INVOKABLE bool isCapabilitySupported(Capability capability) const;
    bool isEnabled() const;
    void setEnabled(bool v);

signals:
    void enabledChanged();

private:
    QFeedbackActuator* d;
};

QML_DECLARE_TYPE(QDeclarativeFeedbackActuator)

#endif // QDECLARATIVEFEEDBACKACTUATOR_P_H
