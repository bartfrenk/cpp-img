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

}}

#endif
