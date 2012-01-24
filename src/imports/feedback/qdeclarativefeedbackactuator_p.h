/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtFeedback module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
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

#include <QtDeclarative/qdeclarative.h>
#include "qfeedbackactuator.h"

QT_USE_NAMESPACE

class QDeclarativeFeedbackActuator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int actuatorId READ actuatorId)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QFeedbackActuator::State state READ state)
    Q_PROPERTY(bool valid READ isValid)
    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged)

public:
    explicit QDeclarativeFeedbackActuator(QObject *parent = 0);
    explicit QDeclarativeFeedbackActuator(QObject *parent, QFeedbackActuator* actuator);
    QFeedbackActuator* feedbackActuator() const;
    int actuatorId() const;
    bool isValid() const;
    QString name() const;
    QFeedbackActuator::State state() const;
    Q_INVOKABLE bool isCapabilitySupported(QFeedbackActuator::Capability capbility) const;
    bool isEnabled() const;
    void setEnabled(bool v);

signals:
    void enabledChanged();

private:
    QFeedbackActuator* d;
};

QML_DECLARE_TYPE(QDeclarativeFeedbackActuator)

#endif // QDECLARATIVEFEEDBACKACTUATOR_P_H
