#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include <QUndoCommand>
#include <QPoint>
#include <vector>
#include <utility>
#include "MandalaModel.h"
#include "Stroke.h"
class DrawCommand : public QUndoCommand
{
public:
    DrawCommand(MandalaModel* model, const std::vector<Stroke>& strokeSegments, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    MandalaModel* _model;
    std::vector<Stroke> _strokeSegments;
};

#endif // DRAWCOMMAND_H
