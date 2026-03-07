#pragma once
#include <vector>
#include "Point.h"
#include "QList"
#include "Command.h"

class MandalaModel {
public:
    MandalaModel();

    void setSlices(int slices) { _slices = slices; }

    std::vector<std::pair<Point, Point> > generateMandalaLines(const Point &p1, const Point &p2,
                                                               const Point &center);

    void setMirrorEffect(const bool mirrorEffectActived) { _mirrorEffect = mirrorEffectActived; }

    void setCommand(Command* command) {_command = command;};

    void executeCommand() {if(_command != nullptr) _command->execute();};

    void setCurrentIdx(int curr) {if(curr >= 0 && curr <= _allLines.size()) _currentIdx = curr;};

    int getCurrentIdx() {return _currentIdx;};

    QList<std::vector<std::pair<Point, Point>>> getAllines() { return _allLines;};

    ~MandalaModel(){ delete _command;};

private:
    int _slices;
    bool _mirrorEffect;
    QList<std::vector<std::pair<Point, Point>>> _allLines; // list of lines a line being a starting point and an ending point
    int _currentIdx;
    Command* _command = nullptr;


    static Point translationToCenter(const Point &p, const Point &center) {
        return {p.x - center.x, p.y - center.y};
    }

    static Point translationFromCenter(const Point &p, const Point &center) {
        return {p.x + center.x, p.y + center.y};
    }

    static Point rotatePoint(const Point &p, double angle);
};
