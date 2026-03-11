#include "SliceCommand.h"

SliceCommand::SliceCommand(MandalaModel* model, const int newSlices,QUndoCommand* parent)
    : QUndoCommand(parent), _model(model),_newSlices(newSlices) {
    setText("Change Slices");
    _oldSlices = _model->getSlices();
}

void SliceCommand::undo() {
    _model->setSlices(_oldSlices);
}

void SliceCommand::redo() {
    _model->setSlices(_newSlices);
}