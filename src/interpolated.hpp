#ifndef INTERPOLATED_HPP
#define INTERPOLATED_HPP

#include "orthotope.hpp"

namespace img {

// statically assert that A is float or double
template <typename I, typename A>
class Bilinear {
public:
    using pixel_t = typename I::pixel_t;
    using coord_t = A;

    Bilinear(const I &base) : base_(base) {};

    Rectangle<coord_t> domain() const {
    }

    pixel_t operator()(const coord_t x, const coord_t y) const {};

private:

    const I base_;
};

template <typename I, typename A>
class NearestNeighbor {
    using pixel_t = typename I::pixel_t;
    using coord_t = A;

    NearestNeighbor(const I &base) :
};

}

#endif
