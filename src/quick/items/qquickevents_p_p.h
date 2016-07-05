/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtQuick module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQUICKEVENTS_P_P_H
#define QQUICKEVENTS_P_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include <private/qtquickglobal_p.h>
#include <qqml.h>

#include <QtCore/qobject.h>
#include <QtGui/qvector2d.h>
#include <QtGui/qevent.h>
#include <QtGui/qkeysequence.h>

QT_BEGIN_NAMESPACE

class QQuickKeyEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int key READ key)
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(int modifiers READ modifiers)
    Q_PROPERTY(bool isAutoRepeat READ isAutoRepeat)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(quint32 nativeScanCode READ nativeScanCode)
    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)

public:
    QQuickKeyEvent()
        : event(QEvent::None, 0, 0)
    {}

    void reset(QEvent::Type type, int key, Qt::KeyboardModifiers modifiers,
               const QString &text = QString(), bool autorep = false, ushort count = 1)
    {
        event = QKeyEvent(type, key, modifiers, text, autorep, count);
        event.setAccepted(false);
    }

    void reset(const QKeyEvent &ke)
    {
        event = ke;
        event.setAccepted(false);
    }

    int key() const { return event.key(); }
    QString text() const { return event.text(); }
    int modifiers() const { return event.modifiers(); }
    bool isAutoRepeat() const { return event.isAutoRepeat(); }
    int count() const { return event.count(); }
    quint32 nativeScanCode() const { return event.nativeScanCode(); }

    bool isAccepted() { return event.isAccepted(); }
    void setAccepted(bool accepted) { event.setAccepted(accepted); }

    Q_REVISION(2) Q_INVOKABLE bool matches(QKeySequence::StandardKey key) const { return event.matches(key); }

private:
    QKeyEvent event;
};

// used in Qt Location
class Q_QUICK_PRIVATE_EXPORT QQuickMouseEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(int button READ button)
    Q_PROPERTY(int buttons READ buttons)
    Q_PROPERTY(int modifiers READ modifiers)
    Q_PROPERTY(int source READ source REVISION 7)
    Q_PROPERTY(bool wasHeld READ wasHeld)
    Q_PROPERTY(bool isClick READ isClick)
    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)

public:
    QQuickMouseEvent()
      : _x(0), _y(0), _button(Qt::NoButton), _buttons(Qt::NoButton), _modifiers(Qt::NoModifier)
      , _source(Qt::MouseEventNotSynthesized), _wasHeld(false), _isClick(false), _accepted(false)
    {}

    void reset(qreal x, qreal y, Qt::MouseButton button, Qt::MouseButtons buttons,
               Qt::KeyboardModifiers modifiers, bool isClick = false, bool wasHeld = false)
    {
        _x = x;
        _y = y;
        _button = button;
        _buttons = buttons;
        _modifiers = modifiers;
        _source = Qt::MouseEventNotSynthesized;
        _wasHeld = wasHeld;
        _isClick = isClick;
        _accepted = true;
    }

    qreal x() const { return _x; }
    qreal y() const { return _y; }
    int button() const { return _button; }
    int buttons() const { return _buttons; }
    int modifiers() const { return _modifiers; }
    int source() const { return _source; }
    bool wasHeld() const { return _wasHeld; }
    bool isClick() const { return _isClick; }

    // only for internal usage
    void setX(qreal x) { _x = x; }
    void setY(qreal y) { _y = y; }
    void setPosition(const QPointF &point) { _x = point.x(); _y = point.y(); }
    void setSource(Qt::MouseEventSource s) { _source = s; }

    bool isAccepted() { return _accepted; }
    void setAccepted(bool accepted) { _accepted = accepted; }

private:
    qreal _x;
    qreal _y;
    Qt::MouseButton _button;
    Qt::MouseButtons _buttons;
    Qt::KeyboardModifiers _modifiers;
    Qt::MouseEventSource _source;
    bool _wasHeld : 1;
    bool _isClick : 1;
    bool _accepted : 1;
};

class QQuickWheelEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x)
    Q_PROPERTY(qreal y READ y)
    Q_PROPERTY(QPoint angleDelta READ angleDelta)
    Q_PROPERTY(QPoint pixelDelta READ pixelDelta)
    Q_PROPERTY(int buttons READ buttons)
    Q_PROPERTY(int modifiers READ modifiers)
    Q_PROPERTY(bool inverted READ inverted)
    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)

public:
    QQuickWheelEvent()
      : _x(0), _y(0), _buttons(Qt::NoButton), _modifiers(Qt::NoModifier)
      , _inverted(false), _accepted(false)
    {}

    void reset(qreal x, qreal y, const QPoint &angleDelta, const QPoint &pixelDelta,
                     Qt::MouseButtons buttons, Qt::KeyboardModifiers modifiers, bool inverted)
    {
        _x = x;
        _y = y;
        _angleDelta = angleDelta;
        _pixelDelta = pixelDelta;
        _buttons = buttons;
        _modifiers = modifiers;
        _accepted = true;
        _inverted = inverted;
    }

    qreal x() const { return _x; }
    qreal y() const { return _y; }
    QPoint angleDelta() const { return _angleDelta; }
    QPoint pixelDelta() const { return _pixelDelta; }
    int buttons() const { return _buttons; }
    int modifiers() const { return _modifiers; }
    bool inverted() const { return _inverted; }
    bool isAccepted() { return _accepted; }
    void setAccepted(bool accepted) { _accepted = accepted; }

private:
    qreal _x;
    qreal _y;
    QPoint _angleDelta;
    QPoint _pixelDelta;
    Qt::MouseButtons _buttons;
    Qt::KeyboardModifiers _modifiers;
    bool _inverted;
    bool _accepted;
};

QT_END_NAMESPACE

QML_DECLARE_TYPE(QQuickKeyEvent)
QML_DECLARE_TYPE(QQuickMouseEvent)
QML_DECLARE_TYPE(QQuickWheelEvent)

#endif // QQUICKEVENTS_P_P_H
