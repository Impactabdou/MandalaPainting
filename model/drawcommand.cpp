#include "drawcommand.h"

DrawCommand::DrawCommand(MandalaModel* model,  const std::vector<Stroke>& strokeSegments, QUndoCommand* parent)
    : QUndoCommand(parent), _model(model), _strokeSegments(strokeSegments)
{
    setText("Draw Stroke");
}

void DrawCommand::undo() {
    _model->removeLastSegments(_strokeSegments.size());
}

void DrawCommand::redo() {
    _model->addStrokeSegments(_strokeSegments);
}
