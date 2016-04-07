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

//TESTED_COMPONENT=src/feedback

#include <QtTest/QtTest>

#include <qfeedbackeffect.h>
#include <qfeedbackactuator.h>

QT_USE_NAMESPACE

class tst_QFeedbackPlugin : public QObject
{
    Q_OBJECT
public:
    tst_QFeedbackPlugin();
    ~tst_QFeedbackPlugin();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void testPlugin();
    void testFileEffect();
    void testThemeEffect();
};

tst_QFeedbackPlugin::tst_QFeedbackPlugin()
{
}

tst_QFeedbackPlugin::~tst_QFeedbackPlugin()
{
}

void tst_QFeedbackPlugin::initTestCase()
{
}

void tst_QFeedbackPlugin::cleanupTestCase()
{
}

void tst_QFeedbackPlugin::init()
{
}

void tst_QFeedbackPlugin::cleanup()
{
}

void tst_QFeedbackPlugin::testThemeEffect()
{
    QVERIFY(QFeedbackEffect::supportsThemeEffect());
    QVERIFY(QFeedbackEffect::playThemeEffect(QFeedbackEffect::Press));
    QVERIFY(!QFeedbackEffect::playThemeEffect(QFeedbackEffect::Release));
}

void tst_QFeedbackPlugin::testFileEffect()
{
    QFeedbackFileEffect fileEffect;
    QVERIFY(QFeedbackFileEffect::supportedMimeTypes().contains("x-test/this is a test"));

    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped);

    fileEffect.setSource(QUrl("load")); // this should call load
    QVERIFY(fileEffect.state() == QFeedbackEffect::Loading);

    fileEffect.setSource(QUrl("ignored")); // not stopped, should fail
    QVERIFY(fileEffect.source() == QUrl("load"));

    QVERIFY(fileEffect.isLoaded());
    fileEffect.setLoaded(true); // should do nothing
    QVERIFY(fileEffect.isLoaded());
    QCOMPARE(fileEffect.duration(), 5678); // from the plugin

    fileEffect.unload(); // should fail, since we're not STOPPED (HMM!!)
    QVERIFY(fileEffect.isLoaded());

    fileEffect.stop();
    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped);
    // Now we should be able to change things again

    // Make sure setting the source to the same thing is a noop
    fileEffect.setSource(fileEffect.source());
    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped);

    // Now unload
    QVERIFY(fileEffect.isLoaded());
    fileEffect.unload();
    QVERIFY(!fileEffect.isLoaded());
    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped);
    QCOMPARE(fileEffect.duration(), 0); // unloaded, shouldn't call?

    // Change the url
    fileEffect.setSource(QUrl("failload"));
    QVERIFY(!fileEffect.isLoaded());
    // Spinning the event loop is necessary for mmk to fail a load
    QTRY_COMPARE(fileEffect.state(), QFeedbackEffect::Stopped);
    QCOMPARE(fileEffect.duration(), 0); // unknown

    fileEffect.setSource(QUrl("load"));
    QVERIFY(fileEffect.isLoaded());
    QVERIFY(fileEffect.state() == QFeedbackEffect::Loading);
    fileEffect.start();
    QVERIFY(fileEffect.state() == QFeedbackEffect::Running);
    fileEffect.start();
    QVERIFY(fileEffect.state() == QFeedbackEffect::Running);
    fileEffect.stop();
    QVERIFY(fileEffect.state() == QFeedbackEffect::Stopped);
    fileEffect.pause();
    QVERIFY(fileEffect.state() == QFeedbackEffect::Paused); // XXX this is a strange transition
}

void tst_QFeedbackPlugin::testPlugin()
{
    QFeedbackHapticsEffect testEffect;
    // first get the actuators.  we want to use the test plugin actuator.
    QFeedbackActuator* testActuator;
    QList<QFeedbackActuator*> actuators = QFeedbackActuator::actuators();
    QCOMPARE(actuators.count(), 2);

    QCOMPARE(actuators.at(0)->name(), QString("test plugin"));
    QCOMPARE(actuators.at(0)->id(), 0);
    QCOMPARE(actuators.at(1)->name(), QString("5555"));
    QCOMPARE(actuators.at(1)->id(), 1);

    // make sure we found the test actuator...
    testActuator = actuators.at(0);

    QCOMPARE(testActuator->name(), QString("test plugin"));
    QCOMPARE(testActuator->id(), 0); // test
    QVERIFY(testActuator->isCapabilitySupported(QFeedbackActuator::Period));
    testActuator->setEnabled(true);
    QVERIFY(!testActuator->isEnabled()); // the test plugin always returns enabled = false.
    testActuator->setEnabled(false);
    QVERIFY(!testActuator->isEnabled()); // the test plugin always returns enabled = false.
    testActuator->setEnabled(true);
    QVERIFY(!testActuator->isEnabled()); // the test plugin always returns enabled = false.
    QCOMPARE(testActuator->state(), QFeedbackActuator::Unknown); // and it always returns state = unknown.
    // XXX TODO: ensure that a "working" plugin returns real values..

    // then, ensure that the test effect uses this actuator.
    testEffect.setActuator(testActuator);

    // it will do nothing, so stick some values in and play it.
    testEffect.setAttackIntensity(0.0);
    testEffect.setAttackTime(250);
    testEffect.setIntensity(1.0);
    testEffect.setDuration(100);
    testEffect.setFadeTime(250);
    testEffect.setFadeIntensity(0.0);
    testEffect.start();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Running);
    testEffect.pause();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Paused);
    testEffect.start();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Running);
    testEffect.stop();
    QVERIFY(testEffect.state() == QFeedbackHapticsEffect::Stopped);
}

QTEST_MAIN(tst_QFeedbackPlugin)

#include "tst_qfeedbackplugin.moc"
