#include "MouseController.h"

MouseController::MouseController() : _drawing(false) {
}

void MouseController::handlePress(const QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        _drawing = true;
        _lastPosition = event->pos();
        _currentPosition = event->pos();
    }
}

void MouseController::handleMove(const QMouseEvent *event) {
    if (_drawing) {
        _currentPosition = event->pos();
    }
}

void MouseController::handleRelease(const QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        _drawing = false;
    }
}

QPoint MouseController::getCurrentPosition() const {
    return _currentPosition;
}

QPoint MouseController::getLastPosition() const {
    return _lastPosition;
}

bool MouseController::isDrawing() const {
    return _drawing;
}
