#ifndef UNDOCOMMAND_H
#define UNDOCOMMAND_H
#include "Command.h"
#include "MandalaModel.h"

class UndoCommand : public Command
{
public:
    UndoCommand(MandalaModel model) : _model(model) {};
    void execute() override;
private:
    MandalaModel _model;
};

#endif // UNDOCOMMAND_H
