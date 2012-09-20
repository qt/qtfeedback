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

#include <qfeedbackactuator.h>

QT_USE_NAMESPACE

class tst_QFeedbackActuator : public QObject
{
    Q_OBJECT
public:
    tst_QFeedbackActuator();
    ~tst_QFeedbackActuator();

public slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

private slots:
    void enumeration();
    void setEnabled();
};

tst_QFeedbackActuator::tst_QFeedbackActuator()
{
}

tst_QFeedbackActuator::~tst_QFeedbackActuator()
{
}

void tst_QFeedbackActuator::initTestCase()
{
}

void tst_QFeedbackActuator::cleanupTestCase()
{
}

void tst_QFeedbackActuator::init()
{
    //the list returned should always be the same with the same order
    QCOMPARE(QFeedbackActuator::actuators(), QFeedbackActuator::actuators());
}

void tst_QFeedbackActuator::cleanup()
{
}


#if defined(HAVE_ACTUATORS) && !defined(Q_OS_SYMBIAN)
//we're on meego/maemo
#define CAPABILITY true //the capabilities are supported through Immersion
#else
#define CAPABILITY false
#endif

void tst_QFeedbackActuator::enumeration()
{
    QList<QFeedbackActuator*> actuators = QFeedbackActuator::actuators();
#ifdef HAVE_ACTUATORS
    QVERIFY(!actuators.isEmpty());
#endif
    foreach(QFeedbackActuator* actuator, actuators) {
        if (actuator->name() == QString("test plugin") || actuator->name() == QString("5555"))
            continue;

        QVERIFY(actuator->isValid());
        QVERIFY(actuator->id() >= 0);
        QCOMPARE(actuator->isCapabilitySupported(QFeedbackActuator::Envelope), CAPABILITY);
        QCOMPARE(actuator->isCapabilitySupported(QFeedbackActuator::Period), CAPABILITY);
        QVERIFY(!actuator->name().isEmpty());
    }

    // Try comparisons
    if (actuators.count() > 1) {
        QFeedbackActuator* a1 = actuators.at(0);
        QFeedbackActuator* a2 = actuators.at(1);
        QFeedbackActuator* a1b = actuators.at(0);
        QFeedbackActuator* a2b = actuators.at(1);
        QVERIFY(a1->id() != a2->id());
//        QVERIFY(*a1 != *a2); // doesn't work, no operator != !!
        QVERIFY(!(*a1 == *a2));

        QVERIFY(*a1 == *a1b);
        QVERIFY(*a2 == *a2b);
    }
}

void tst_QFeedbackActuator::setEnabled()
{
   foreach(QFeedbackActuator* actuator, QFeedbackActuator::actuators()) {
       if (actuator->name() == QString("test plugin") || actuator->name() == QString("5555"))
            continue;
        //this test might not always be true because you ight not be allowed to change the enabled property
        actuator->setEnabled(false);
        QVERIFY(!actuator->isEnabled());
        actuator->setEnabled(true);
        QVERIFY(actuator->isEnabled());
    }
}




QTEST_MAIN(tst_QFeedbackActuator)

#include "tst_qfeedbackactuator.moc"
