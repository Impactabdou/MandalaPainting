#include "undocommand.h"

void UndoCommand::execute() {
    _model.setCurrentIdx(_model.getCurrentIdx()- 1);
}
