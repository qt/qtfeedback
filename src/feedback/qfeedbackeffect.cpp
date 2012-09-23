/****************************************************************************
**
** Copyright (C) 2012 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the QtFeedback module of the Qt Toolkit.
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

#include "qfeedbackeffect.h"
#include "qfeedbackeffect_p.h"
#include "qfeedbackplugininterfaces.h"

#include <QtCore>
#include <QDebug>


QT_BEGIN_NAMESPACE

/*!
    \class QFeedbackEffect
    \brief The QFeedbackEffect class is the abstract base class for feedback effects.
    \ingroup feedback
    \inmodule QtFeedback

    It represents an effect to provide feedback to a person (i.e., an effect that
    affect human senses). The technology available today usually only
    provides haptic effects, which deal with the sense of touch, and audio effects. The
    QFeedbackHapticsEffect and QFeedbackFileEffect are implementations
    of haptic effects and can be used to control a mobile device's
    vibrator.  In addition, the QFeedbackFileEffect can also be used to play
    audio feedback.

    Feedback effects have a duration, which is measured in
    milliseconds. Subclasses reimplement duration() to inform how long
    the effect lasts.  The duration is the total time the effect will
    last, and thus includes any envelope modifiers (attack and fade).

    At any given time, a feedback effect is in one of four states:
    Loading, Stopped, Running, or Paused. See the
    \l{QFeedbackEffect::}{State} enum documentation for further
    details. Subclasses must reimplement state() to report which
    state an effect is in, and setState() to receive state change
    requests. The start(), pause(), and stop() slots calls
    setState() with the corresponding new \l{QFeedbackEffect::}{State}.  Changes
    in state are reported through the stateChanged() signal and may happen
    asynchronously some time after the state change request.

    A system often has a set of standard feedback effects for user
    interface interaction (e.g., button clicks). The
    \l{QFeedbackEffect::}{Effect} describes the standard effects
    that QFeedbackEffect supports. It is named so because the effects
    often depend on the theme of the user interface. You can play
    these effects using the playThemeEffect() function.

    \code
        QFeedbackEffect::playThemeEffect(QFeedbackEffect::Press);
    \endcode

    The playThemeEffect() function returns true if the effect was
    played successfully. An effect may not be played if the system does
    not support it or if an error occurred.
*/

/*!
    \fn void QFeedbackEffect::error(QFeedbackEffect::ErrorType error) const

    This signal is emitted by subclasses if an \a error occurred during
    playback of an effect. The \l{QFeedbackEffect::}{ErrorType} enum
    describes the errors that can be reported.
*/

/*!
    \fn void QFeedbackEffect::stateChanged()

    This signal is emitted by subclasses when the \l State of the
    effect changes.

    \sa state()
*/

/*!
    \enum QFeedbackEffect::State

    This enum describes the state of the effect. An effect will be in
    one of these states.

    \value Stopped The effect is not running. This is the initial
    state. The state changes to either Loading when loading an effect
    or to Running when the effect is started by calling start().  When
    an effect has finished playing, it will enter the Stopped state
    again.

    \value Paused The effect is paused. Calling start() will resume it.

    \value Running The effect is running. You can control the current state
    by calling the stop() or pause() functions.

    \value Loading The effect is loading. That can happen when loading
    is done asynchronously.  When the effect has loaded, the state will change
    to either Running (if start() has been called) or Stopped.

    \sa state()
*/


/*!
    \enum QFeedbackEffect::ErrorType

    This enum describes the possible errors happening on the effect.

    \value UnknownError An unknown error occurred.

    \value DeviceBusy The feedback could not start because the device is busy.

    \sa error()
*/

/*!
    \enum QFeedbackEffect::Effect

    This enum describes all possible effect types. Effects might
    be tactile, or audio or visual.

    Not all platforms and devices have distinct effects for each type.

    \value Effect.Undefined - Undefined feedback. No feedback is given.
    \value Effect.Press - Feedback for when the screen is pressed.
    \value Effect.Release - Feedback for touch release.
    \value Effect.PressWeak - A weak feedback for press.
    \value Effect.ReleaseWeak - A weak feedback for release.
    \value Effect.PressStrong - A strong feedback for press.
    \value Effect.ReleaseStrong - A strong feedback for release.
    \value Effect.DragStart - Feedback for when dragging starts.
    \value Effect.DragDropInZone - Feedback for when dragging ends and touch is released inside a drop zone.
    \value Effect.DragDropOutOfZone - Feedback for when dragging ends and touch is released outside a drop zone.
    \value Effect.DragCrossBoundary - Feedback for when crossing a boundary while dragging.
    \value Effect.Appear - Feedback for when an item is shown.
    \value Effect.Disappear - Feedback for when an item is closed.
    \value Effect.Move - Feedback for dragging on screen.
    \value NumberOfEffects The number of built-in effects.
    \value UserEffect The starting point for any user defined effects, where supported.
 */

/*!
    \enum QFeedbackEffect::Duration
    This enum describes the possible effect predefined duration types.  Generally a specific
    milliseconds value can be supplied instead of one of these values.

    \value Infinite  Infinite effect duration
  */

/*!
    \property QFeedbackEffect::state
    \brief state of the feedback effect.

    This returns the state of the feedback effect.  The \l State enumeration reports
    the possible states.
*/

/*!
    \property QFeedbackEffect::duration
    \brief duration of the feedback effect, in milliseconds.

    In some cases the duration will be unknown, which will be reported as 0.  If the duration
    is infinite, QFeedbackEffect::Infinite will be returned.  Some subclasses may have
    more than one type of duration (for example, \l QFeedbackHapticsEffect), and this
    property will return the total duration of the effect.
*/

/*!
    Constructs the QFeedbackEffect base class, and passes \a parent to
    QObject's constructor.  This is called by the classes that inherit
    from this class.
*/
QFeedbackEffect::QFeedbackEffect(QObject *parent) : QObject(parent)
{
}

/*!
    \fn void QFeedbackEffect::start()

    Starts playing the effect. If an error occurs the
    error() signal will be emitted.

    \sa stop()
*/
void QFeedbackEffect::start()
{
    setState(Running);
}

/*!
    \fn void QFeedbackEffect::stop()

    Stops a playing effect. If an error occurs the
    error() signal will be emitted.

    \sa start(), pause(), setState()
*/
void QFeedbackEffect::stop()
{
    setState(Stopped);
}

/*!
    \fn void QFeedbackEffect::pause()

    Pauses a playing effect. If an error occurs the
    error() signal will be emitted.  Not all systems
    support pausing an effect during playback.
*/
void QFeedbackEffect::pause()
{
    setState(Paused);
}

/*!
    \fn QFeedbackEffect::playThemeEffect(Effect effect)

    This function plays \a effect instantly and returns true if the
    effect could be played; otherwise, returns false.
*/
bool QFeedbackEffect::playThemeEffect(Effect effect)
{
    if (QFeedbackThemeInterface *iface = QFeedbackThemeInterface::instance())
        return iface->play(effect);
    return false;
}

/*!
    \fn QFeedbackEffect::supportsThemeEffect()

    Returns true if playing themed feedback is available.

*/
bool QFeedbackEffect::supportsThemeEffect()
{
    return QFeedbackThemeInterface::instance() != 0;
}

/*!
    \class QFeedbackHapticsEffect
    \ingroup feedback
    \inmodule QtFeedback
    \brief The QFeedbackHapticsEffect class allows you to play a haptics effect.

    A haptics effect is an effect that takes advantage of the sense of
    touch. Most mobile devices today supports one such effect,
    vibration, which will then be the default when you create a
    QFeedbackHapticsEffect.

    A haptics effect has a few parameters that must be set up before
    it can be played:

    \list
        \li duration(): The total duration of the effect in milliseconds.
        \li intensity(): The intensity, e.g., how hard the device will vibrate.
    \endlist

    An effect can, for example, be set up as follows:

    \omit I'm right that this is all that is required to be set? \endomit
    \code
        QFeedbackHapticsEffect rumble;
        rumble.setIntensity(1.0);
        rumble.setDuration(100);
    \endcode

    You can now start() the effect.

    \code
        rumble.start();
    \endcode

    At any given time, the effect is in one of four states:
    \l{QFeedbackEffect::}{Stopped}, \l{QFeedbackEffect::}{Paused},
    \l{QFeedbackEffect::}{Running}, or \l{QFeedbackEffect::}{Loading}.
    You can request a state change by calling start(), pause(), or
    stop(). The state is queried with state().

    The haptics effect also supports a fade-in of the effect. For
    vibration, this means that the vibration will grow (or sink) in
    intensity from when the effect starts until intensity() is
    reached. You can set that up as follows:

    \code
        rumble.setAttackIntensity(0.0);
        rumble.setAttackTime(250);
    \endcode

    Attack intensity is the start intensity and attack time is the
    duration of the fade-in. We have a similar fade-out:

    \code
        rumble.setFadeTime(250);
        rumble.setFadeIntensity(0.0);
    \endcode

    When using fade-in and fade-out the total duration of the haptics
    effect will be: duration(); the main intensity() will be played for
    (duration() - (attackTime() + fadeTime())) milliseconds.

    A QFeedbackHapticsEffect is played on an
    \l{QFeedbackHapticsEffect::}{actuator()}, which is the physical component that
    performs the effect. You can query if other actuators are
    available - see the QFeedbackActuator::actuators() function
    documentation for details.

    Errors occurring during playback are notified through the
    error() signal.

    \sa QFeedbackActuator
*/

/*!
    \fn virtual void QFeedbackEffect::setState(State state) = 0

    Requests the effect to change its State to change to the specified \a state.

    Subclasses reimplement this function to handle state change requests
    for the effect.
*/

/*!
    Constructs the QFeedbackHapticsEffect class, and passes \a parent to
    QObject's constructor.  The default QFeedbackActuator will be used.

    \sa QFeedbackActuator::actuators()
*/
QFeedbackHapticsEffect::QFeedbackHapticsEffect(QObject *parent) : QFeedbackEffect(parent), priv(new QFeedbackHapticsEffectPrivate)
{
    setActuator(0);
}


/*!
    Destroys this effect and stops the feedback if it is running.
*/
QFeedbackHapticsEffect::~QFeedbackHapticsEffect()
{
    stop();
}

/*!
    \property QFeedbackHapticsEffect::duration
    \brief the expected duration of the effect.

    This property defines the total duration of the feedback effect, in milliseconds.
    It includes the duration of any fade-in or fade-out parts, if any, in non-periodic
    effects, and includes all repetitions of the period in periodic-effects, if any.

    If the duration is set to a value less than attackTime() + fadeTime(), or less
    than the period() of the effect, the waveform which will result is
    backend-specific.

    \sa fadeTime(), attackTime(), period()
*/
int QFeedbackHapticsEffect::duration() const
{
    return priv->duration;
}
void QFeedbackHapticsEffect::setDuration(int msecs)
{
    if (priv->duration == msecs)
        return;
    priv->duration = msecs;
    QFeedbackHapticsInterface::instance()->updateEffectProperty(this, QFeedbackHapticsInterface::Duration);
}

/*!
    \property QFeedbackHapticsEffect::intensity
    \brief the intensity of the effect.

    This property defines the intensity of the feedback effect.
    The value can be between 0 and 1.

    For non-periodic effects, the effect will be at this intensity for
    (duration() - (attackTime() + fadeTime())) milliseconds.
    For periodic effects, the effect will be at this intensity once per
    period for (period() - (attackTime() + fadeTime())) milliseconds.
*/
qreal QFeedbackHapticsEffect::intensity() const
{
    return priv->intensity;
}
void QFeedbackHapticsEffect::setIntensity(qreal intensity)
{
    if (priv->intensity == intensity)
        return;
    priv->intensity = intensity;
    QFeedbackHapticsInterface::instance()->updateEffectProperty(this, QFeedbackHapticsInterface::Intensity);
}

/*!
    \property QFeedbackHapticsEffect::attackTime
    \brief the duration of the fade-in effect.

    This property defines the duration of the fade-in effect in milliseconds.
    The effect will ramp up (or down) from attackIntensity() to intensity() in attackTime() milliseconds.

    If the attack time is set to a value such that attackTime() + fadeTime()
    is greater than duration() for non-periodic effects, or greater than
    period() for periodic effects, the waveform which will result is
    backend-specific.

    \sa duration(), period()
*/
int QFeedbackHapticsEffect::attackTime() const
{
    return priv->attackTime;
}
void QFeedbackHapticsEffect::setAttackTime(int msecs)
{
    if (priv->attackTime == msecs)
        return;
    priv->attackTime = msecs;
    QFeedbackHapticsInterface::instance()->updateEffectProperty(this, QFeedbackHapticsInterface::AttackTime);
}

/*!
    \property QFeedbackHapticsEffect::attackIntensity
    \brief the initial intensity of the effect.

    This property defines the initial intensity of the effect, before it fades in.
    It is usually lower than \l intensity.  The effect will ramp up (or down) from
    attackIntensity() to intensity() in attackTime() milliseconds.
*/
qreal QFeedbackHapticsEffect::attackIntensity() const
{
    return priv->attackIntensity;
}
void QFeedbackHapticsEffect::setAttackIntensity(qreal intensity)
{
    if (priv->attackIntensity == intensity)
        return;
    priv->attackIntensity = intensity;
    QFeedbackHapticsInterface::instance()->updateEffectProperty(this, QFeedbackHapticsInterface::AttackIntensity);
}

/*!
    \property QFeedbackHapticsEffect::fadeTime
    \brief the duration of the fade-out effect.

    This property defines the duration of the fade-out effect in milliseconds.
    The effect will ramp down (or up) from intensity() to fadeIntensity() in fadeTime() milliseconds.

    If the fade time is set to a value such that attackTime() + fadeTime()
    is greater than duration() for non-periodic effects, or greater than
    period() for periodic effects, the waveform which will result is
    backend-specific.

    \sa duration(), period()
*/
int QFeedbackHapticsEffect::fadeTime() const
{
    return priv->fadeTime;
}
void QFeedbackHapticsEffect::setFadeTime(int msecs)
{
    if (priv->fadeTime == msecs)
        return;
    priv->fadeTime = msecs;
    QFeedbackHapticsInterface::instance()->updateEffectProperty(this, QFeedbackHapticsInterface::FadeTime);
}

/*!
    \property QFeedbackHapticsEffect::fadeIntensity
    \brief the final intensity of the effect.

    This property defines the final intensity of the effect, after it fades out.
    It is usually lower than \l intensity.
    The effect will ramp down (or up) from intensity() to fadeIntensity() in fadeTime() milliseconds.
*/
qreal QFeedbackHapticsEffect::fadeIntensity() const
{
    return priv->fadeIntensity;
}
void QFeedbackHapticsEffect::setFadeIntensity(qreal intensity)
{
    if (priv->fadeIntensity == intensity)
        return;
    priv->fadeIntensity = intensity;
    QFeedbackHapticsInterface::instance()->updateEffectProperty(this, QFeedbackHapticsInterface::FadeIntensity);
}

/*!
    \property QFeedbackHapticsEffect::actuator
    \brief the actuator on which the effect operates.

    This property defines the actuator on which the effect operates.  You can only
    change the actuator used when the effect is stopped.  Setting a null actuator
    resets the effect to use the default actuator.
*/
QFeedbackActuator* QFeedbackHapticsEffect::actuator() const
{
    return priv->actuator;
}
void QFeedbackHapticsEffect::setActuator(QFeedbackActuator *actuator)
{
    if (state() != Stopped) {
        qWarning("QFeedbackHapticsEffect::setActuator: The effect is not stopped");
        return;
    }

    if (actuator) {
        priv->actuator = actuator;
    } else {
        QList<QFeedbackActuator*> list = QFeedbackActuator::actuators();
        if  (!list.isEmpty()) {
            priv->actuator = list.first();
        } else {
            priv->actuator = new QFeedbackActuator(this);
        }
    }
}

/*!
    \property QFeedbackHapticsEffect::period
    \brief set the period for the effect.

    It has a default value of -1, which means that it is not a periodic effect.
    You can only change the period when the effect is stopped.
    The duration of the effect should be set to a value larger than the
    period of the effect if you wish the periodicity to be discernable.
    \note Not all actuators support periodic effects

    The period defines the total length of the periodic envelope, which will
    be repeated up until duration() milliseconds has elapsed.  For a periodic
    effect, the intensity will start at attackIntensity(), ramp to intensity()
    (where it stays for (period() - (attackTime() + fadeTime())) milliseconds),
    then ramp to fadeIntensity().  This waveform will be repeated as many times
    as required until the duration() has elapsed.

    If the period is set to a value which is less than attackTime() + fadeTime(),
    the waveform which will result is backend-specific.
*/
int QFeedbackHapticsEffect::period() const
{
    return priv->period;
}
void QFeedbackHapticsEffect::setPeriod(int msecs)
{
    if (state() != Stopped) {
        qWarning("QFeedbackHapticsEffect::setPeriod: the period can only be changed if the effect is stopped");
        return;
    }
    priv->period = msecs;
}

/*!
    \internal
*/
void QFeedbackHapticsEffect::setState(State state)
{
    State oldState = this->state();
    if (oldState != state) {
        QFeedbackHapticsInterface::instance()->setEffectState(this, state);
        emit stateChanged();
    }
}

/*!
    \internal
*/
QFeedbackEffect::State QFeedbackHapticsEffect::state() const
{
    return QFeedbackHapticsInterface::instance()->effectState(this);
}

/*!
\internal
    \class QFeedbackFileEffect
    \ingroup feedback
    \inmodule QtFeedback
    \brief The QFeedbackFileEffect class allows to play feedback from a file.

    Several different mime types may be supported on a system, including
    both haptic data files, and audio files.

    The files containing haptics data are usually suffixed \c .ivt.
    The feedback is usually varying in
    \l{QFeedbackHapticsEffect::}{intensity()}, and is for that reason
    often referred to as a "haptic tune". They are created, for
    instance, from music files where the feedback is based on a
    specific feature in the audio data. For example, you could have a
    phone vibrating along with the bass of a rock song.

    Although Qt Feedback does not let you record \c .ivt files, it lets
    you play them back using the QFeedbackFileEffect class. Setting
    up a QFeedbackFileEffect and starting it is done as follows:

    \code
        QFeedbackFileEffect hapticTune;
        hapticTune.setSource(QUrl::fromLocalFile("mySavedRumble.ivt"));
        hapticTune.load();
        hapticTune.start();
    \endcode

    As with other \l{QFeedbackEffect}s, QFeedbackFileEffect is at any
    given time in one of four states: \l{QFeedbackEffect::}{Loading},
    \l{QFeedbackEffect::}{Running}, \l{QFeedbackEffect::}{Paused}, or
    \l{QFeedbackEffect::}{Stopped}. You request state changes with
    start(), pause(), and stop().

    You can load() and unload() the file at will to free resources or
    be as fast as possible. The file must be loaded before it can be
    started, and it cannot be unloaded while playing. After the file is
    loaded, you can query its duration().  Some mime types may not
    support duration information - in these cases, 0 will be returned.

    QFeedbackFileEffect reports errors through the error() signal.

    \sa QFeedbackHapticsEffect
*/


/*!
    \internal
*/
void QFeedbackFileEffectPrivate::loadFinished(bool success)
{
    loaded = success;
    if( !success)
        backendUsed = -1;
}


/*!
    \internal
    Constructs the QFeedbackFileEffect class, and passes \a parent to
    QObject's constructor.
*/
QFeedbackFileEffect::QFeedbackFileEffect(QObject *parent) : QFeedbackEffect(parent), priv(new QFeedbackFileEffectPrivate(this))
{
}

/*!
    \internal
    Stops the feedback and unloads the file if necessary.
*/
QFeedbackFileEffect::~QFeedbackFileEffect()
{
    setLoaded(false); //ensures we unload the file and frees resources
}

/*!
    \reimp
*/
int QFeedbackFileEffect::duration() const
{
    return QFeedbackFileInterface::instance()->effectDuration(this);
}

/*!
    \internal
    \property QFeedbackFileEffect::source
    \brief the url of the file that is loaded.

    Setting that property will automatically unload the previous file (if any) and load the new one.
    Some backends may not support all URL schemes - for example, they may only support
    local files.

    You can only change the source of an effect when it is stopped.
*/
QUrl QFeedbackFileEffect::source() const
{
    return priv->url;
}
void QFeedbackFileEffect::setSource(const QUrl &source)
{
    if (state() != QFeedbackEffect::Stopped) {
        qWarning("QFeedbackFileEffect::setSource: can't set the file while the feedback is running");
        return;
    }
    if (source != priv->url) {
        setLoaded(false);
        priv->url = source;
        setLoaded(true);
    }
}

/*!
    \internal
    \property QFeedbackFileEffect::loaded
    \brief reports if the file has been successfully loaded.
*/
bool QFeedbackFileEffect::isLoaded() const
{
    return priv->loaded;
}
void QFeedbackFileEffect::setLoaded(bool load)
{
    if (priv->loaded == load)
        return;

    if (state() != QFeedbackEffect::Stopped) {
        qWarning() << "QFeedbackFileEffect::setLoaded: can't load/unload a file while the effect is not stopped";
        return;
    }

    QFeedbackFileInterface::instance()->setLoaded(this, load);
}


/*!
    \internal
    \fn void QFeedbackFileEffect::load()

    Makes sure that the file associated with the feedback object is loaded.
    It will be automatically loaded when the setSource() or start() functions
    are called.
*/
void QFeedbackFileEffect::load()
{
    setLoaded(true);
}

/*!
    \internal
    \fn void QFeedbackFileEffect::unload()

    makes sure that the file associated with the feedback object is unloaded.
    It will be automatically unloaded when the setSource function is called with
    another file or the object is destroyed.
*/
void QFeedbackFileEffect::unload()
{
    setLoaded(false);
}


/*!
    \internal
    \fn QStringList QFeedbackFileEffect::supportedMimeTypes()

    returns the MIME types supported for playing effects from file.
*/
QStringList QFeedbackFileEffect::supportedMimeTypes()
{
    return QFeedbackFileInterface::instance()->supportedMimeTypes();
}


/*!
    \reimp
*/
void QFeedbackFileEffect::setState(State newState)
{
    State oldState = state();
    if (oldState != newState) {
        if (newState != Stopped && state() == Stopped)
            load(); // makes sure the file is loaded
        QFeedbackFileInterface::instance()->setEffectState(this, newState);
        emit stateChanged();
    }
}

/*!
    \reimp
*/
QFeedbackEffect::State QFeedbackFileEffect::state() const
{
    return QFeedbackFileInterface::instance()->effectState(this);
}

QT_END_NAMESPACE
