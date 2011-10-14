/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
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

#ifndef QDECLARATIVEFILEEFFECT_P_H
#define QDECLARATIVEFILEEFFECT_P_H

#include <QtDeclarative/qdeclarative.h>
#include "qdeclarativefeedbackeffect_p.h"

QT_USE_NAMESPACE

class QDeclarativeFileEffect : public QDeclarativeFeedbackEffect
{
    Q_OBJECT

    Q_PROPERTY(bool loaded READ isLoaded WRITE setLoaded NOTIFY loadedChanged)
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(QStringList supportedMimeTypes READ supportedMimeTypes)

public:
    explicit QDeclarativeFileEffect(QObject *parent = 0);
    bool isLoaded() const;
    void setLoaded(bool v);
    QUrl source() const;
    void setSource(const QUrl & url);
    QStringList supportedMimeTypes();

signals:
    void loadedChanged();
    void sourceChanged();

public slots:
    void load();
    void unload();

private:
    QFeedbackFileEffect* d;
};

QML_DECLARE_TYPE(QDeclarativeFileEffect)

#endif // QDECLARATIVEFILEEFFECT_P_H