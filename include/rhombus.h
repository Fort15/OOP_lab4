#pragma once

#include "figure.h"
#include <memory>
#include <iostream>

template <Number T>
class Rhombus : public Figure<T> {
private:
    T cx, cy, d1, d2;

    std::unique_ptr<Point<T>[]> points;

public:
    Rhombus();
    Rhombus(T cx, T cy, T d1, T d2);


    Point<T> center() const override;
    operator double() const override;
    void print(std::ostream& os) const override;
    void input(std::istream& is) override;
    bool operator==(const Figure<T>& right_operand) const override;

    void calc_points() const;
};

template <Number T>
Rhombus<T>::Rhombus() : cx(0), cy(0), d1(1), d2(1) {
    points = std::make_unique<Point<T>[]>(4);
    calc_points(); 
}

template <Number T>
Rhombus<T>::Rhombus(T cx, T cy, T d1, T d2)
    : cx(cx), cy(cy), d1(d1), d2(d2) {
    points = std::make_unique<Point<T>[]>(4);
    calc_points();
}

template <Number T>
Point<T> Rhombus<T>::center() const {
    return Point<T>{cx, cy};
}

template <Number T>
Rhombus<T>::operator double() const {
    return static_cast<double>(d1 * d2) / 2.0;
}

template <Number T>
void Rhombus<T>::print(std::ostream& os) const {
    calc_points();
    os << "Координаты вершин ромба (начиная с верхней " 
          "точки и по часовой стрелке)\n";
    for (int i = 0; i < 4; ++i) {
        os << "(" << points[i].x << "," << points[i].y << ") ";
    }
    os << "\n";
}

template <Number T>
void Rhombus<T>::input(std::istream& is) {
    is >> cx >> cy >> d1 >> d2;
    calc_points();
}

template <Number T>
bool Rhombus<T>::operator==(const Figure<T>& right_operand) const {
    const Rhombus* rh = dynamic_cast<const Rhombus<T>*>(&right_operand);
    if (!rh) return false;
    return std::abs(cx - rh->cx) < 1e-12 && std::abs(cy - rh->cy) < 1e-12 &&
           std::abs(d1 - rh->d1) < 1e-12 && std::abs(d2 - rh->d2) < 1e-12;
}

template <Number T>
void Rhombus<T>::calc_points() const {
    points[0] = Point<T>{cx, cy + d1 / static_cast<T>(2)};
    points[1] = Point<T>{cx + d2 / static_cast<T>(2), cy};
    points[2] = Point<T>{cx, cy - d1 / static_cast<T>(2)};
    points[3] = Point<T>{cx - d2 / static_cast<T>(2), cy};
}