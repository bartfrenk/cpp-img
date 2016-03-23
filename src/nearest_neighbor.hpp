#ifndef NEAREST_NEIGHBOR_HPP
#define NEAREST_NEIGHBOR_HPP

#include <cmath>
#include <type_traits>
#include "orthotope.hpp"
#include "mapped.hpp"

namespace img {
namespace core {

template <typename I, typename A>
class NearestNeighbor {
public:
    using pixel_t = typename I::pixel_t;
    using coord_t = A;

    NearestNeighbor(const I &base) : base_(base) {
        static_assert(std::is_integral<typename I::coord_t>::value,
                      "No use interpolating an image with non-integral coordinates");
        static_assert(std::is_floating_point<A>::value,
                      "No use interpolating to non-floating point coordinates");
    };

    pixel_t operator()(const coord_t x, const coord_t y) const {
        using grid_t = typename I::pixel_t;
        return base_((grid_t) std::round(x), (grid_t) std::round(y));
    }

    template <typename G>
    Mapped<G, NearestNeighbor<I, A>> map(const G &fn) {
        return img::core::map(fn, *this);
    }

    Rectangle<coord_t> domain() const {
        return base_.domain.convert();
    }
private:
    const I base_;
};


template <typename A, typename I>
NearestNeighbor<I, A> nearest_neighbor(const I &base) {
    return NearestNeighbor<I, A>(base);
}

}
}
#endif
