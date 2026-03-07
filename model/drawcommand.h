#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include <QUndoCommand>
#include <QPoint>
#include <vector>
#include <utility>
#include "MandalaModel.h"

class DrawCommand : public QUndoCommand
{
public:
    DrawCommand(MandalaModel* model, const std::vector<std::pair<QPoint, QPoint>>& strokeSegments, QUndoCommand* parent = nullptr);

    void undo() override;
    void redo() override;

private:
    MandalaModel* _model;
    std::vector<std::pair<QPoint, QPoint>> _strokeSegments;
};

#endif // DRAWCOMMAND_H
