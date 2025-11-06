#pragma once

#include <concepts>

template <typename T>
concept Number = std::is_default_constructible_v<T> && ( std::integral<T> || std::floating_point<T> );

template <Number T>
struct Point {
    T x, y;


    Point() = default;
    Point(T x, T y) : x(x), y(y) {}
};
