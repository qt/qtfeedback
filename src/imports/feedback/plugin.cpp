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

#include <QtDeclarative/qdeclarativeextensionplugin.h>
#include <QtDeclarative/qdeclarative.h>

#include "qdeclarativehapticseffect_p.h"
#include "qdeclarativefileeffect_p.h"
#include "qdeclarativethemeeffect_p.h"
#include "qdeclarativefeedbackeffect_p.h"
#include "qdeclarativefeedbackactuator_p.h"

QT_USE_NAMESPACE

class QDeclarativeFeedbackPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri)
    {
        const char *currentUri = "QtFeedback";
        // Support for this will be removed. See: https://bugreports.qt-project.org/browse/QTBUG-24285
        const char *oldUri = "Qt.feedback";
        Q_ASSERT(QLatin1String(uri) == currentUri || QLatin1String(uri) == oldUri);
        Q_UNUSED(uri);

        int major = 5;
        int minor = 0;
        qmlRegisterUncreatableType<QDeclarativeFeedbackEffect>(currentUri, major, minor, "Feedback", "this is the feedback namespace");
        qmlRegisterUncreatableType<QDeclarativeFeedbackEffect>(currentUri, major, minor, "FeedbackEffect", "this is the base feedback effect class");
        qmlRegisterType<QDeclarativeFeedbackActuator>(currentUri, major, minor, "Actuator");
        qmlRegisterType<QDeclarativeFileEffect>(currentUri, major, minor, "FileEffect");
        qmlRegisterType<QDeclarativeHapticsEffect>(currentUri, major, minor, "HapticsEffect");
        qmlRegisterType<QDeclarativeThemeEffect>(currentUri, major, minor, "ThemeEffect");
        qmlRegisterUncreatableType<QDeclarativeFeedbackEffect>(oldUri, major, minor, "Feedback", "this is the feedback namespace");
        qmlRegisterUncreatableType<QDeclarativeFeedbackEffect>(oldUri, major, minor, "FeedbackEffect", "this is the base feedback effect class");
        qmlRegisterType<QDeclarativeFeedbackActuator>(oldUri, major, minor, "Actuator");
        qmlRegisterType<QDeclarativeFileEffect>(oldUri, major, minor, "FileEffect");
        qmlRegisterType<QDeclarativeHapticsEffect>(oldUri, major, minor, "HapticsEffect");
        qmlRegisterType<QDeclarativeThemeEffect>(oldUri, major, minor, "ThemeEffect");
    }
};

#include "plugin.moc"

Q_EXPORT_PLUGIN2(declarative_feedback, QDeclarativeFeedbackPlugin)
