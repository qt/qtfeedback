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

#include <QtQml/QQmlExtensionPlugin>

#include "qdeclarativehapticseffect_p.h"
#include "qdeclarativefileeffect_p.h"
#include "qdeclarativethemeeffect_p.h"
#include "qdeclarativefeedbackeffect_p.h"
#include "qdeclarativefeedbackactuator_p.h"

QT_USE_NAMESPACE

static QObject *createDeclarativeThemeEfect(QQmlEngine *engine, QJSEngine *jsengine)
{
    Q_UNUSED(engine)
    Q_UNUSED(jsengine)

    return new QDeclarativeThemeEffect;
}

class QDeclarativeFeedbackPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface" FILE "plugin.json")

public:
    virtual void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("QtFeedback"));

        int major = 5;
        int minor = 0;
        qmlRegisterUncreatableType<QDeclarativeFeedbackEffect>(uri, major, minor, "Feedback", "this is the feedback namespace");
        qmlRegisterUncreatableType<QDeclarativeFeedbackEffect>(uri, major, minor, "FeedbackEffect", "this is the base feedback effect class");
        qmlRegisterType<QDeclarativeFeedbackActuator>(uri, major, minor, "Actuator");
        qmlRegisterType<QDeclarativeFileEffect>(uri, major, minor, "FileEffect");
        qmlRegisterType<QDeclarativeHapticsEffect>(uri, major, minor, "HapticsEffect");
        qmlRegisterType<QDeclarativeThemeEffect>(uri, major, minor, "ThemeEffect");
        qmlRegisterSingletonType<QDeclarativeThemeEffect>("QtFeedback", major, minor, "EffectPlayer", createDeclarativeThemeEfect);
    }
};

#include "plugin.moc"
