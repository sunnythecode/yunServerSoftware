#ifndef JSGAMESEND_H
#define JSGAMESEND_H

#include <QObject>
#include <joystickhandler.h>
#include <gamedata.h>

class JSGameSend : public QObject
{
    Q_OBJECT
public:
    explicit JSGameSend();
    ~JSGameSend();
signals:

public slots:
};

#endif // JSGAMESEND_H
