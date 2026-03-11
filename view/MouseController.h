#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H
#include <QPoint>
#include <QMouseEvent>

class MouseController {
public :
    MouseController();

    void handlePress(QMouseEvent *event);

    void handleMove(QMouseEvent *event);

    void handleRelease(QMouseEvent *event);

    QPoint getCurrentPosition() const;

    QPoint getLastPosition() const;

    bool isDrawing() const;

    void setLastPosition(QPoint p2) { _lastPosition = p2; }

private:
    QPoint _currentPosition;
    QPoint _lastPosition;
    bool _drawing;
};
#endif
