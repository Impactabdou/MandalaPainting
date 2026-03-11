#include "drawcommand.h"

DrawCommand::DrawCommand(MandalaModel* model,  const QVector<Stroke>& strokeSegments, QUndoCommand* parent)
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
