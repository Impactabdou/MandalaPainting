#pragma once

struct Point {
    double x;
    double y;

    Point() : x(0), y(0) {
    }

    Point(double x, double y) : x(x), y(y) {
    }

    Point operator+(const Point &other) const {
        return {x + other.x, y + other.y};
    }

    Point operator-() const {
        return {-x, y};
    }
};
