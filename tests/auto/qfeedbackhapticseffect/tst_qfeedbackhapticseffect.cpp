/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the Qt Mobility Components.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
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

class tst_QFeedbackHapticsEffect : public QObject
{
    Q_OBJECT
public:
    tst_QFeedbackHapticsEffect();
    ~tst_QFeedbackHapticsEffect();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void initialization();
    void envelope_data();
    void envelope();
    void startStop_data();
    void startStop();
    void themeSupport();

};

tst_QFeedbackHapticsEffect::tst_QFeedbackHapticsEffect()
{
}

tst_QFeedbackHapticsEffect::~tst_QFeedbackHapticsEffect()
{
}

void tst_QFeedbackHapticsEffect::initTestCase()
{
}

void tst_QFeedbackHapticsEffect::cleanupTestCase()
{
}

void tst_QFeedbackHapticsEffect::init()
{
#ifdef Q_OS_SYMBIAN
    //we need that head start for the eventloop to be responsive
    QTest::qWait(1000);
#endif
}

void tst_QFeedbackHapticsEffect::cleanup()
{
}


void tst_QFeedbackHapticsEffect::initialization()
{
    QFeedbackHapticsEffect effect;
    if (QFeedbackActuator::actuators().isEmpty()) {
        QVERIFY(!effect.actuator()->isValid());
    } else {
        QVERIFY(effect.actuator()->isValid());
        QCOMPARE(effect.actuator(), QFeedbackActuator::actuators().first());
    }

    // actuators from other plugins need to be verified.
    //test default values
    QCOMPARE(effect.duration(), 250); //250ms is the default length for effects
    QCOMPARE(effect.intensity(), qreal(1));
    QCOMPARE(effect.attackTime(), 0);
    QCOMPARE(effect.attackIntensity(), qreal(0));
    QCOMPARE(effect.fadeTime(), 0);
    QCOMPARE(effect.fadeIntensity(), qreal(0));
    QCOMPARE(effect.period(), -1);
    QCOMPARE(effect.state(), QFeedbackEffect::Stopped);

}

void tst_QFeedbackHapticsEffect::envelope_data()
{
    QTest::addColumn<int>("duration");
    QTest::addColumn<qreal>("intensity");
    QTest::addColumn<int>("attackTime");
    QTest::addColumn<qreal>("attackIntensity");
    QTest::addColumn<int>("fadeTime");
    QTest::addColumn<qreal>("fadeIntensity");
    QTest::addColumn<int>("period");

    QTest::newRow("TEST1")        <<  300 << qreal(.2) <<   1 << qreal(.2) <<   2 << qreal(1) <<  -1;
    QTest::newRow("TEST2")        <<  500 <<  qreal(1) << 100 << qreal(.5) <<   0 << qreal(0) <<  -1;
    QTest::newRow("TEST3")        <<  250 << qreal(.8) << 150 <<  qreal(1) << 150 << qreal(1) <<  -1;
    QTest::newRow("TEST period")  << 1000 <<  qreal(1) << 150 <<  qreal(1) << 150 << qreal(1) << 150;
}

void tst_QFeedbackHapticsEffect::envelope()
{
    QFETCH(int, duration);
    QFETCH(qreal, intensity);
    QFETCH(int, attackTime);
    QFETCH(qreal, attackIntensity);
    QFETCH(int, fadeTime);
    QFETCH(qreal, fadeIntensity);
    QFETCH(int, period);

    QFeedbackHapticsEffect effect;

    // actuators from other plugins need to be verified.
    effect.setDuration(duration);
    QCOMPARE(effect.duration(), duration);

    effect.setIntensity(intensity);
    QCOMPARE(effect.intensity(), intensity);

    effect.setAttackTime(attackTime);
    QCOMPARE(effect.attackTime(), attackTime);

    effect.setAttackIntensity(attackIntensity);
    QCOMPARE(effect.attackIntensity(), attackIntensity);

    effect.setFadeTime(fadeTime);
    QCOMPARE(effect.fadeTime(), fadeTime);

    effect.setFadeIntensity(fadeIntensity);
    QCOMPARE(effect.fadeIntensity(), fadeIntensity);

    effect.setPeriod(period);
    QCOMPARE(effect.period(), period);

    //test all the values at once
    QCOMPARE(effect.duration(), duration);
    QCOMPARE(effect.intensity(), intensity);
    QCOMPARE(effect.attackTime(), attackTime);
    QCOMPARE(effect.attackIntensity(), attackIntensity);
    QCOMPARE(effect.fadeTime(), fadeTime);
    QCOMPARE(effect.fadeIntensity(), fadeIntensity);
    QCOMPARE(effect.period(), period);
}


void tst_QFeedbackHapticsEffect::startStop_data()
{
    envelope_data();
}

void tst_QFeedbackHapticsEffect::startStop()
{
    qRegisterMetaType<QFeedbackEffect::ErrorType>("QFeedbackEffect::ErrorType");
    if (QFeedbackActuator::actuators().isEmpty())
        QSKIP("this test requires to have actuators");

    QList<QFeedbackActuator*> actuators = QFeedbackActuator::actuators();

    QFETCH(int, duration);
    QFETCH(qreal, intensity);
    QFETCH(int, attackTime);
    QFETCH(qreal, attackIntensity);
    QFETCH(int, fadeTime);
    QFETCH(qreal, fadeIntensity);
    QFETCH(int, period);

    QFeedbackHapticsEffect effect;
    QSignalSpy errorspy(&effect, SIGNAL(error(QFeedbackEffect::ErrorType)));
    QSignalSpy stateSpy(&effect, SIGNAL(stateChanged()));

    effect.setDuration(duration);
    effect.setIntensity(intensity);
    effect.setAttackTime(attackTime);
    effect.setAttackIntensity(attackIntensity);
    effect.setFadeTime(fadeTime);
    effect.setFadeIntensity(fadeIntensity);
    effect.setPeriod(period);

    QCOMPARE(effect.state(), QFeedbackHapticsEffect::Stopped);
    QCOMPARE(effect.actuator(), actuators.at(0));

    // Double set a few properties (shouldn't call the backend)
    effect.setAttackTime(attackTime);
    QVERIFY(effect.attackTime() == attackTime);

    effect.setFadeTime(fadeTime);
    QVERIFY(effect.fadeTime() == fadeTime);

    // Test setting to a non default actuator and then back again
    if (actuators.count() > 1) {
        effect.setActuator(actuators.at(1));
        QCOMPARE(effect.actuator(), actuators.at(1));

        effect.setActuator(0);
        QCOMPARE(effect.actuator(), actuators.at(0));

        // noop
        effect.setActuator(actuators.at(0));
        QCOMPARE(effect.actuator(), actuators.at(0));
    }

    // Now start
    QVERIFY(stateSpy.isEmpty());
    effect.start();
    QVERIFY(errorspy.isEmpty());

    // This seems a little risky
    QTRY_COMPARE(effect.state(), QFeedbackHapticsEffect::Running);
    QVERIFY(errorspy.isEmpty());
    QCOMPARE(stateSpy.count(), 1); // stopped to start

    effect.pause();
    QCOMPARE(effect.state(), QFeedbackHapticsEffect::Paused);
    QCOMPARE(stateSpy.count(), 2);

    // Now try to change a few properties (should be refused because of !Stopped)
    effect.setPeriod(period + 100);
    QVERIFY(effect.period() == period);

    QFeedbackActuator* actuator = effect.actuator();
    effect.setActuator(0);
    QVERIFY(effect.actuator() == actuator);

    effect.start();
    QCOMPARE(effect.state(), QFeedbackHapticsEffect::Running);
    QCOMPARE(stateSpy.count(),  3);

    QTRY_COMPARE(effect.state(), QFeedbackHapticsEffect::Stopped);
    QVERIFY(errorspy.isEmpty());
    QCOMPARE(stateSpy.count(), 4);
}


void tst_QFeedbackHapticsEffect::themeSupport()
{
    const bool supportsTheme = QFeedbackEffect::supportsThemeEffect();

    if (!supportsTheme)
        QSKIP("No theme support");
    int numberOfSupportedEffects = 0;
    for (int i = 0; i < QFeedbackEffect::NumberOfEffects; ++i) {
        if (QFeedbackEffect::playThemeEffect(QFeedbackEffect::Effect(i)))
            numberOfSupportedEffects++;
        QTest::qWait(250); //let's make sure the device is ready again
    }

    QVERIFY(numberOfSupportedEffects > 0);
}

QTEST_MAIN(tst_QFeedbackHapticsEffect)

#include "tst_qfeedbackhapticseffect.moc"
