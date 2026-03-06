#pragma once
#include <QPoint>
#include <vector>

class MandalaModel {
public:
    MandalaModel();

    void setSlices(int slices) { _slices = slices; }

    std::vector<std::pair<QPoint, QPoint> > generateMandalaLines(
        const QPoint &p1,
        const QPoint &p2,
        const QPoint &center
    );

    void setMirror(bool mirror) { _mirror = mirror; }

private:
    int _slices;
    bool _mirror;
};
