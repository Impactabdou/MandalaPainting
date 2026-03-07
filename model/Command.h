#ifndef COMMAND_H
#define COMMAND_H
#include "qpoint.h"
class Command {
public:
    virtual ~Command() = default;
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual void draw(const QPoint lastpos, const QPoint currpos) = 0;
};
#endif // COMMAND_H
