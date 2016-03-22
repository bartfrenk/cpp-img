#ifndef MAPPED_HPP
#define MAPPED_HPP

#include <functional>
#include "lazy.hpp"

namespace img {
namespace core {

template <typename I, typename P>
class Mapped {
public:
    using pixel_t = P;
    using coord_t = typename I::coord_t;

    Mapped(const std::function<pixel_t(typename I::pixel_t)> &fn, const I &base) :
        fn_(fn), base_(base) {};


    pixel_t operator()(const coord_t x, const coord_t y) const {
        return fn_(base_(x, y));
    }

    /** Evaluate image and return stored result. */
    Stored<coord_t, pixel_t> materialize() const {
        return img::core::materialize(*this);
    };

    Rectangle<coord_t> domain() const {
        return base_.domain();
    }
private:

    const std::function<pixel_t(typename I::pixel_t)> fn_;
    const I base_;

};

template <typename I, typename P>
Mapped<I, P> map(const std::function<P(typename I::pixel_t)> &fn, const I &base)
{
    return Mapped<I, P>(fn, base);
};

}}

#endif
