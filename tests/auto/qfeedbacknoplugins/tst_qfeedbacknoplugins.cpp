/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
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

//TESTED_COMPONENT=src/feedback

#include <QtTest/QtTest>

#include <qfeedbackeffect.h>
#include <qfeedbackactuator.h>

QT_USE_NAMESPACE

class tst_QFeedbackNoPlugins : public QObject
{
    Q_OBJECT
public:
    tst_QFeedbackNoPlugins();
    ~tst_QFeedbackNoPlugins();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void testHapticEffect();
    void testFileEffect();
    void testThemeEffect();
    void testActuators();
};

tst_QFeedbackNoPlugins::tst_QFeedbackNoPlugins()
{
    // This turns off plugin loading in unit test builds
    qApp->setProperty("QFEEDBACK_TEST_NO_PLUGINS", 1);
}

tst_QFeedbackNoPlugins::~tst_QFeedbackNoPlugins()
{
}

void tst_QFeedbackNoPlugins::initTestCase()
{
}

void tst_QFeedbackNoPlugins::cleanupTestCase()
{
}

void tst_QFeedbackNoPlugins::init()
{
}

void tst_QFeedbackNoPlugins::cleanup()
{
}

void tst_QFeedbackNoPlugins::testThemeEffect()
{
    // No plugins
    QVERIFY(!QFeedbackEffect::supportsThemeEffect());
    QVERIFY(!QFeedbackEffect::playThemeEffect(QFeedbackEffect::ThemeBasic));
    QVERIFY(!QFeedbackEffect::playThemeEffect(QFeedbackEffect::ThemeBasicButton));
}

void tst_QFeedbackNoPlugins::testFileEffect()
{
    QFeedbackFileEffect fileEffect;
    QVERIFY(QFeedbackFileEffect::supportedMimeTypes().isEmpty());

    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped);

    fileEffect.setSource(QUrl("load")); // this should call load
    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped); // fail :D
    QVERIFY(!fileEffect.isLoaded());
    fileEffect.setLoaded(true);
    QVERIFY(!fileEffect.isLoaded());
    fileEffect.setLoaded(false);
    QVERIFY(!fileEffect.isLoaded());
    fileEffect.start();
    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped); // fail :D
}

void tst_QFeedbackNoPlugins::testHapticEffect()
{
    QFeedbackHapticsEffect testEffect;

    // it will do nothing, so stick some values in and play it.
    testEffect.setAttackIntensity(0.0);
    testEffect.setAttackTime(250);
    testEffect.setIntensity(1.0);
    testEffect.setDuration(100);
    testEffect.setFadeTime(250);
    testEffect.setFadeIntensity(0.0);
    testEffect.start();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Stopped);
    testEffect.pause();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Stopped);
    testEffect.start();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Stopped);
    testEffect.stop();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Stopped);
}


void tst_QFeedbackNoPlugins::testActuators()
{
    QList<QFeedbackActuator*> actuators = QFeedbackActuator::actuators();

    // No plugins == no actuators
    QVERIFY(actuators.isEmpty());

    // Create a default one, anyway
    QFeedbackActuator a;

    QVERIFY(a.isValid() == false);
    QVERIFY(a.name().isEmpty());

    QCOMPARE(a.isCapabilitySupported(QFeedbackActuator::Envelope), false);
    QCOMPARE(a.isCapabilitySupported(QFeedbackActuator::Period), false);

    a.setEnabled(false);
    QVERIFY(!a.isEnabled());
    a.setEnabled(true);
    QVERIFY(!a.isEnabled());
}

QTEST_MAIN(tst_QFeedbackNoPlugins)

#include "tst_qfeedbacknoplugins.moc"
