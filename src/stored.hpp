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

template <typename P>
class Stored {
public:
    using coord_t = size_t;
    using pixel_t = P;

    Stored(const coord_t width, const coord_t height)
        : Stored(width, height, width) {};

    Stored(const coord_t width, const coord_t height, const coord_t pitch)
        : Stored(Rectangle<coord_t>(width, height), pitch) {};

    Stored(const Rectangle<coord_t> domain) : Stored(domain, domain.width()) {};

    pixel_t& operator()(const coord_t x, const coord_t y) {
        return buffer_.get()[y * pitch_ + x];
    }

    pixel_t operator()(const coord_t x, const coord_t y) const {
        return buffer_.get()[y * pitch_ + x];
    }

    Rectangle<coord_t> domain() const {
        return domain_;
    }

private:
    Stored(const Rectangle<coord_t> domain, const coord_t pitch)
        : domain_(domain),
          pitch_(pitch),
          buffer_(new P[pitch * domain.height()], array_deleter<P>()) {};

    const Rectangle<coord_t> domain_;
    const coord_t pitch_;
    std::shared_ptr<P> buffer_;

};

template <template <typename P> class J, typename I>
auto materialize(const I& img) -> J<typename I::pixel_t> const {
    // TODO: static checking that coord_t is an integral type.
    using coord_t = typename I::coord_t;
    using pixel_t = typename I::pixel_t;

    const size_t width = static_cast<size_t>(img.domain().hi[0] - img.domain().lo[0]);
    const size_t height = static_cast<size_t>(img.domain().hi[1] - img.domain().lo[1]);

    J<pixel_t> stored(width, height);

    const coord_t x0 = img.domain().lo[0];
    const coord_t y0 = img.domain().lo[1];

    for (size_t y = 0; y < height; ++y)
        for (size_t x = 0; x < width; ++x)
            stored(x, y) = img(x + x0, y + y0);

    return stored;
}

}}

#endif
