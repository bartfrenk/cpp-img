#ifndef POINT_HPP
#define POINT_HPP

#include <cstddef>
#include <initializer_list>
#include "types.hpp"

template <typename A, const dim_t d>
class Point {
public:
    Point(std::initializer_list<A> coords) {
        if (coords.size() != d) { // throw exception
        }

        size_t index = 0;
        for (auto x : coords) {
            coords_[index++] = x;
        }
    }

    A& operator[](const dim_t i) {
        return coords_[i];
    }
    A operator[](const dim_t i) const {
        return coords_[i];
    }
    bool operator==(const Point<A, d> &that) const {
        for (size_t i = 0; i < d; ++i)
            if (coords_[i] != that.coords_[i]) return false;
        return true;
    }
    bool operator!=(const Point<A, d> &that) const {
        return !(*this == that);
    }
private:
    A coords_[d];
};

#endif
