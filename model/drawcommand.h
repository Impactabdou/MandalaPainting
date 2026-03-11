#ifndef DRAWCOMMAND_H
#define DRAWCOMMAND_H

#include <QUndoCommand>
#include <QVector>
#include "MandalaModel.h"
#include "Stroke.h"

class DrawCommand : public QUndoCommand {
public:
    DrawCommand(MandalaModel *model, const QVector<Stroke> &strokeSegments, QUndoCommand *parent = nullptr);

    void undo() override;

    void redo() override;

private:
    MandalaModel *_model;
    QVector<Stroke> _strokeSegments;
};

#endif // DRAWCOMMAND_H
