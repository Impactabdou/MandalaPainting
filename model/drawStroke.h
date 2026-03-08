#ifndef DRAWSTROKE_H
#define DRAWSTROKE_H
#include "Command.h"
#include "MandalaModel.h"

class DrawStroke : public Command
{
public:
    UndoCommand(MandalaModel* model) : _model(model) {};
    void execute() override;
private:
    MandalaModel* _model;
};

#endif // DRAWSTROKE_H
