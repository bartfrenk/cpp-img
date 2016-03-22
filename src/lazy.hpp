#ifndef LAZY_HPP
#define LAZY_HPP

#include <iostream>

#include "stored.hpp"

namespace img {
namespace core {


template <typename I>
auto materialize(const I& img) -> Stored<typename I::coord_t, typename I::pixel_t> const {
    // TODO: static checking that coord_t is an integral type.
    using coord_t = typename I::coord_t;
    using pixel_t = typename I::pixel_t;

    Stored<coord_t, pixel_t> stored(img.domain());
    for (coord_t y = img.domain().lo; y < img.domain().hi.y; ++y)
        for (coord_t x = img.domain().lo.x; x < img.domain().hi.x; ++x)
            stored(x, y) = img(x, y);

    return stored;
}

template <typename I>
void print(std::ostream &os, const I &img) {
    auto domain = img.domain();
    for (size_t i = domain.lo[0]; i < domain.hi[0]; ++i) {
        for (size_t j = domain.lo[1]; j < domain.hi[1]; ++j)
            os << img(i, j) << " ";
        os << std::endl;
    }
}


}}

#endif
