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

#include <qtest.h>
#include <QtQml/qqmlcomponent.h>
#include <QtQml/qqmlengine.h>
#include <qfeedbackeffect.h>
#include <qfeedbackactuator.h>
#include <QSignalSpy>

#ifdef Q_OS_SYMBIAN
// In Symbian OS test data is located in applications private dir
#define SRCDIR "."
#endif

Q_DECLARE_METATYPE(QFeedbackEffect::Effect);

class tst_qdeclarativefeedback : public QObject

{
    Q_OBJECT
public:
    tst_qdeclarativefeedback();

private slots:
    void hapticsEffect();
    void fileEffect();
    void actuator();
    void themeEffect();

private:
    QQmlEngine engine;
};

tst_qdeclarativefeedback::tst_qdeclarativefeedback()
{
}

void tst_qdeclarativefeedback::hapticsEffect()
{
    QQmlComponent component(&engine);
    component.loadUrl(QUrl::fromLocalFile(SRCDIR "/data/hapticseffect.qml"));

    QObject *hapticsEffect = component.create();
    QVERIFY(hapticsEffect != 0);

    QSignalSpy stateSpy(hapticsEffect, SIGNAL(stateChanged()));
    QVERIFY(stateSpy.isValid());
    QCOMPARE(stateSpy.count(), 0);

    QCOMPARE(hapticsEffect->property("attackIntensity").toReal(), 0.0);
    QCOMPARE(hapticsEffect->property("attackTime").toInt(), 250);
    QCOMPARE(hapticsEffect->property("intensity").toReal(), 1.0);
    QCOMPARE(hapticsEffect->property("duration").toInt(), 100);
    QCOMPARE(hapticsEffect->property("fadeTime").toInt(), 250);
    QCOMPARE(hapticsEffect->property("fadeIntensity").toReal(), 0.0);
    QVERIFY(!hapticsEffect->property("actuator").isNull());
    QCOMPARE(hapticsEffect->property("state").toInt(), (int)(QFeedbackEffect::Stopped));

    hapticsEffect->setProperty("attackIntensity", 0.2);
    QCOMPARE(hapticsEffect->property("attackIntensity").toReal(), 0.2);
    hapticsEffect->setProperty("attackTime", 500);
    QCOMPARE(hapticsEffect->property("attackTime").toInt(), 500);
    hapticsEffect->setProperty("intensity", 0.8);
    QCOMPARE(hapticsEffect->property("intensity").toReal(), 0.8);
    hapticsEffect->setProperty("duration", 500);
    QCOMPARE(hapticsEffect->property("duration").toInt(), 500);
    hapticsEffect->setProperty("fadeTime", 500);
    QCOMPARE(hapticsEffect->property("fadeTime").toInt(), 500);
    hapticsEffect->setProperty("fadeIntensity", 0.2);
    QCOMPARE(hapticsEffect->property("fadeIntensity").toReal(), 0.2);

    if (!hapticsEffect->property("availableActuators").toList().isEmpty()) {
      QCOMPARE(hapticsEffect->property("running").toBool(), false);
      QCOMPARE(hapticsEffect->property("paused").toBool(), false);
      QCOMPARE(hapticsEffect->property("state").toInt(), (int)(QFeedbackEffect::Stopped));

      hapticsEffect->setProperty("running", true);
      QCOMPARE(hapticsEffect->property("running").toBool(), true);
      QCOMPARE(hapticsEffect->property("paused").toBool(), false);
      QCOMPARE(stateSpy.count(), 1);
      QCOMPARE(hapticsEffect->property("state").toInt(), (int)(QFeedbackEffect::Running));

      hapticsEffect->setProperty("paused", true);
      // XXX make sure we just test dummy backend
      QCOMPARE(hapticsEffect->property("running").toBool(), false);
      QCOMPARE(hapticsEffect->property("paused").toBool(), true);
      QCOMPARE(stateSpy.count(), 2);
      QCOMPARE(hapticsEffect->property("state").toInt(), (int)(QFeedbackEffect::Paused));

      hapticsEffect->setProperty("running", true);
      QCOMPARE(hapticsEffect->property("running").toBool(), true);
      QCOMPARE(hapticsEffect->property("paused").toBool(), false);
      QCOMPARE(stateSpy.count(), 3);
      QCOMPARE(hapticsEffect->property("state").toInt(), (int)(QFeedbackEffect::Running));

      hapticsEffect->setProperty("running", false);
      QCOMPARE(hapticsEffect->property("running").toBool(), false);
      QCOMPARE(hapticsEffect->property("paused").toBool(), false);
      QCOMPARE(stateSpy.count(), 4);
      QCOMPARE(hapticsEffect->property("state").toInt(), (int)(QFeedbackEffect::Stopped));
    }
    delete hapticsEffect;
}

void tst_qdeclarativefeedback::fileEffect()
{
    QQmlComponent component(&engine);
    component.loadUrl(QUrl::fromLocalFile(SRCDIR "/data/fileeffect.qml"));

    QObject *fileEffect = component.create();
    QVERIFY(fileEffect != 0);

    QCOMPARE(fileEffect->property("source").toUrl(), QUrl("qrc:nonexistingfile.haptic"));
    QCOMPARE(fileEffect->property("loaded").toBool(), false);
    QTRY_COMPARE(fileEffect->property("state").toInt(), (int)(QFeedbackEffect::Stopped));

    QCOMPARE(fileEffect->property("running").toBool(), false);
    QCOMPARE(fileEffect->property("paused").toBool(), false);
    fileEffect->setProperty("running", true);
    fileEffect->setProperty("paused", true);

    // dummy backend
    QTRY_COMPARE(fileEffect->property("running").toBool(), false);
    QTRY_COMPARE(fileEffect->property("paused").toBool(), false);

    delete fileEffect;
}

void tst_qdeclarativefeedback::actuator()
{
    QQmlComponent component(&engine);
    component.loadUrl(QUrl::fromLocalFile(SRCDIR "/data/actuator.qml"));

    QObject *actuator = component.create();
    QVERIFY(actuator != 0);
    QCOMPARE(actuator->property("enabled").toBool(), false);

    delete actuator;
}

void tst_qdeclarativefeedback::themeEffect()
{
    QQmlComponent component(&engine);
    component.loadUrl(QUrl::fromLocalFile(SRCDIR "/data/themeeffect.qml"));

    // We don't export this class, but we're just poking at properties anyway
    QObject *dte = component.create();
    QCOMPARE(component.errorString(), QString());
    QVERIFY(dte != 0);

    // Test the effect property gets assigned
    QMetaProperty p = dte->metaObject()->property(dte->metaObject()->indexOfProperty("effect"));
    QCOMPARE(p.read(dte).value<int>(), (int)QFeedbackEffect::Press);

    p = dte->metaObject()->property(dte->metaObject()->indexOfProperty("supported"));
    QCOMPARE(p.read(dte).value<bool>(), QFeedbackEffect::supportsThemeEffect());

    delete dte;

    component.loadUrl(QUrl::fromLocalFile(SRCDIR "/data/themeeffect2.qml"));

    dte = component.create();
    QCOMPARE(component.errorString(), QString());

    QVERIFY(dte != 0);
    // Effect property as a string
    p = dte->metaObject()->property(dte->metaObject()->indexOfProperty("effect"));
    QCOMPARE(p.read(dte).value<int>(), (int)QFeedbackEffect::Press);

    delete dte;

    // Now test the default method
    component.loadUrl(QUrl::fromLocalFile(SRCDIR "/data/themeeffect3.qml"));

    dte = component.create();
    QCOMPARE(component.errorString(), QString());
    QVERIFY(dte != 0);

    // Well, we can only verify that through a dummy plugin (TODO). verified through qdebug atm :)

    delete dte;
}

QTEST_MAIN(tst_qdeclarativefeedback)

#include "tst_qdeclarativefeedback.moc"
