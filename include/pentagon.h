#pragma once

#include "figure.h"
#include <memory>
#include <iostream>
#include <cmath>

template <Number T>
class Pentagon : public Figure<T> {
private:
    T cx, cy, radius;

    std::unique_ptr<Point<T>[]> points;

public:
    Pentagon();
    Pentagon(T cx, T cy, T radius);


    Point<T> center() const override;
    operator double() const override;
    void print(std::ostream& os) const override;
    void input(std::istream& is) override;
    bool operator==(const Figure<T>& right_operand) const override;
    Pentagon& operator=(const Pentagon& other);
    Pentagon& operator=(Pentagon&& other) noexcept;

    void calc_points() const;
};

template <Number T>
Pentagon<T>::Pentagon() : cx(0), cy(0), radius(1) {
    points = std::make_unique<Point<T>[]>(5);
    calc_points(); 
}

template <Number T>
Pentagon<T>::Pentagon(T cx, T cy, T radius)
    : cx(cx), cy(cy), radius(radius) {
    points = std::make_unique<Point<T>[]>(5);
    calc_points();
}

template <Number T>
Point<T> Pentagon<T>::center() const {
    return Point<T>{cx, cy};
}

template <Number T>
Pentagon<T>::operator double() const {
    return 2.5 * static_cast<double>(radius * radius) * std::sin(2.0 * M_PI / 5.0);
}

template <Number T>
void Pentagon<T>::print(std::ostream& os) const {
    calc_points();
    os << "Координаты вершин пятиугольника (начиная с верхней " 
          "и по часовой стрелке)\n";
    for (int i = 0; i < 5; ++i) {
        os << "(" << points[i].x << "," << points[i].y << ") ";
    }
    os << "\n";
}

template <Number T>
void Pentagon<T>::input(std::istream& is) {
    is >> cx >> cy >> radius;
    calc_points();
}

template <Number T>
bool Pentagon<T>::operator==(const Figure<T>& right_operand) const {
    const Pentagon* pt = dynamic_cast<const Pentagon<T>*>(&right_operand);
    if (!pt) return false;
    return std::abs(cx -pt->cx) < 1e-12 && std::abs(cy - pt->cy) < 1e-12 &&
           std::abs(radius - pt->radius) < 1e-12; 
}

template <Number T>
void Pentagon<T>::calc_points() const {
    double angle_beetwen = 2.0 * M_PI / 5.0;
    double first_angle = M_PI / 2.0;

    for (int i = 0; i < 5; ++i) {
        double angle = first_angle - i * angle_beetwen;
        points[i] = Point<T>{cx + static_cast<T>(radius * std::cos(angle)),
                             cy + static_cast<T>(radius * std::sin(angle))};
    }
}

template<Number T>
Pentagon<T>& Pentagon<T>::operator=(const Pentagon<T>& other) {
    if (this != &other) {
        cx = other.cx;
        cy = other.cy;
        radius = other.radius;

        points = std::make_unique<Point<T>[]>(5);
        for (int i = 0; i < 5; ++i) {
            points[i] = other.points[i];
        }
    }
    return *this;
}

template<Number T>
Pentagon<T>& Pentagon<T>::operator=(Pentagon<T>&& other) noexcept {
    if (this != &other) {
        cx = other.cx;
        cy = other.cy;
        radius = other.radius;
        points = std::move(other.points); 
    }
    return *this;
}