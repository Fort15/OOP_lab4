#pragma once

#include "figure.h"
#include <memory>
#include <iostream>

template <Number T>
class Trapezoid : public Figure<T> {
private:
    T cx_bottom, cy_bottom, bottom, top, h;

    std::unique_ptr<Point<T>[]> points;

public:
    Trapezoid();
    Trapezoid(T cx_bottom, T cy_bottom, T bottom, T top, T h);


    Point<T> center() const override;
    operator double() const override;
    void print(std::ostream& os) const override;
    void input(std::istream& is) override;
    bool operator==(const Figure<T>& right_operand) const override;

    void calc_points() const;
};

template <Number T>
Trapezoid<T>::Trapezoid() : cx_bottom(0), cy_bottom(0), bottom(2), top(1), h(1) {
    points = std::make_unique<Point<T>[]>(4);
    calc_points(); 
}

template <Number T>
Trapezoid<T>::Trapezoid(T cx_bottom, T cy_bottom, T bottom, T top, T h)
    : cx_bottom(cx_bottom), cy_bottom(cy_bottom), bottom(bottom), top(top), h(h) {
    points = std::make_unique<Point<T>[]>(4);
    calc_points();
}

template <Number T>
Point<T> Trapezoid<T>::center() const {
    T y_center = cy_bottom + h * (static_cast<T>(2) * bottom + top) / (static_cast<T>(3) * (bottom + top));
    return Point<T>{cx_bottom, y_center};
}

template <Number T>
Trapezoid<T>::operator double() const {
    return static_cast<double>(bottom + top) * static_cast<double>(h) / 2.0;
}

template <Number T>
void Trapezoid<T>::print(std::ostream& os) const {
    calc_points();
    os << "Координаты вершин трапеции (начиная с верхней " 
          "левой точки и по часовой стрелке)\n";
    for (int i = 0; i < 4; ++i) {
        os << "(" << points[i].x << "," << points[i].y << ") ";
    }
    os << "\n";
}

template <Number T>
void Trapezoid<T>::input(std::istream& is) {
    is >> cx_bottom >> cy_bottom >> bottom >> top >> h;
    calc_points();
}

template <Number T>
bool Trapezoid<T>::operator==(const Figure<T>& right_operand) const {
    const Trapezoid* tr = dynamic_cast<const Trapezoid<T>*>(&right_operand);
    if (!tr) return false;
    return std::abs(cx_bottom - tr->cx_bottom) < 1e-12 && std::abs(cy_bottom - tr->cy_bottom) < 1e-12 &&
           std::abs(bottom - tr->bottom) < 1e-12 && std::abs(top - tr->top) < 1e-12 && 
           std::abs(h - tr->h) < 1e-12;
}

template <Number T>
void Trapezoid<T>::calc_points() const {
    points[0] = Point<T>{cx_bottom - top / static_cast<T>(2), cy_bottom + h};
    points[1] = Point<T>{cx_bottom + top / static_cast<T>(2), cy_bottom + h};
    points[2] = Point<T>{cx_bottom + bottom / static_cast<T>(2), cy_bottom};
    points[3] = Point<T>{cx_bottom - bottom / static_cast<T>(2), cy_bottom};
}