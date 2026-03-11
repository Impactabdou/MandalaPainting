#ifndef  SLICECOMMAND_H
#define SLICECOMMAND_H
#include <QUndoCommand>
#include "MandalaModel.h"

class SliceCommand : public QUndoCommand {
public:
    SliceCommand(MandalaModel *model, int newSlices, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    MandalaModel *_model;
    int _newSlices;
    int _oldSlices;
};
#endif

