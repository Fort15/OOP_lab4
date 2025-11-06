#pragma once


#include "point.h"
#include <iostream>


template <Number T>
class Figure {
    friend std::ostream &operator<<(std::ostream &os, const Figure<T> &figure) {
        figure.print(os);
        return os;
    }
    
    friend std::istream &operator>>(std::istream &is, Figure<T> &figure) {
        figure.input(is);
        return is;
    }


public:
    virtual ~Figure() = default;
    
    virtual Point<T> center() const = 0;

    virtual operator double() const = 0;

    virtual bool operator==(const Figure<T>& right_operand) const = 0;

    virtual void print(std::ostream& os) const = 0;
    virtual void input(std::istream& is) = 0;
};