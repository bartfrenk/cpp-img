#ifndef STORED_HPP
#define STORED_HPP

#include <cstddef>
#include <memory>
#include "orthotope.hpp"

namespace {

/** Custom deleter to use with shared_ptr to an array. */
template <typename P>
struct array_deleter {
    void operator()(P const * ptr)
    {
        delete[] ptr;
    }
};

}

namespace img {
namespace core {

template <typename A, typename P>
class Stored {
public:
    using coord_t = A;
    using pixel_t = P;

    Stored(const Rectangle<coord_t> domain, const coord_t pitch)
        : domain_(domain),
          pitch_(pitch),
          buffer_(new P[pitch * domain.height()], array_deleter<P>()) {};

    Stored(const coord_t width, const coord_t height)
        : Stored(width, height, width) {};

    Stored(const coord_t width, const coord_t height, const coord_t pitch)
        : Stored(Rectangle<coord_t>(width, height), (pitch)) {};

    Stored(const Rectangle<coord_t> domain) : Stored(domain, domain.width()) {};

    pixel_t& operator()(const coord_t x, const coord_t y) {
        return buffer_.get()[(y - domain_.lo[1]) * pitch_ + (x - domain_.lo[0])];
    }

    pixel_t operator()(const coord_t x, const coord_t y) const {
        return buffer_.get()[(y - domain_.lo[1]) * pitch_ + (x - domain_.lo[0])];
    }

    Rectangle<coord_t> domain() const {
        return domain_;
    }

private:
    const Rectangle<coord_t> domain_;
    const coord_t pitch_;
    std::shared_ptr<P> buffer_;

};

template <typename I>
auto materialize(const I& img) -> Stored<typename I::coord_t, typename I::pixel_t> const {
    // TODO: static checking that coord_t is an integral type.
    using coord_t = typename I::coord_t;
    using pixel_t = typename I::pixel_t;

    Stored<coord_t, pixel_t> stored(img.domain());
    for (coord_t y = img.domain().lo[1]; y < img.domain().hi[1]; ++y)
        for (coord_t x = img.domain().lo[0]; x < img.domain().hi[0]; ++x)
            stored(x, y) = img(x, y);

    return stored;
}

}}

#endif
