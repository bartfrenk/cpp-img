#ifndef ORTHOTOPE_HPP
#define ORTHOTOPE_HPP

#include "types.hpp"
#include "point.hpp"

/* Represents a Cartesian product of intervals of the form [a, b). */
template <typename A, const dim_t d>
struct Orthotope {

    Orthotope(const Point<A, d> &lo, const Point<A, d> &hi) : lo(lo), hi(hi) {};

    template <typename B>
    Orthotope<B, d> convert() {
        return Orthotope(convert<B>(lo), convert<B>(hi));
    }

    bool operator==(const Orthotope &that) const {
        return this->lo == that.lo && this->hi == that.hi;
    }

    bool operator!=(const Orthotope &that) const {
        return !(*this == that);
    }

    Point<A, d> lo;
    Point<A, d> hi;
};

template <typename A>
struct Rectangle : Orthotope<A, 2> {

    Rectangle(const A width, const A height) :
        Orthotope<A, 2>(Point<A, 2>({0, 0}), Point<A, 2>({width, height})) {};

    A width() const { return Orthotope<A, 2>::hi[0] - Orthotope<A, 2>::lo[0]; }
    A height() const { return Orthotope<A, 2>::hi[1] - Orthotope<A, 2>::lo[1]; }
};

#endif
