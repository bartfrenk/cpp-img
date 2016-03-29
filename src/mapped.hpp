#ifndef MAPPED_HPP
#define MAPPED_HPP

#include <functional>
#include <type_traits>
#include "orthotope.hpp"
#include "stored.hpp"

namespace img {
namespace core {

template <typename F, typename I>
class Mapped;

template <typename F, typename I>
Mapped<F, I> map(const F &fn, const I &base) {
    return Mapped<F, I>(fn, base);
};

template <typename F, typename I>
class Mapped {
public:
    Mapped(const F &fn, const I &base) : fn_(fn), base_(base) {};

    using pixel_t = typename std::result_of<F(typename I::pixel_t)>::type;
    using coord_t = typename I::coord_t;

    pixel_t operator()(const coord_t x, const coord_t y) const {
        return fn_(base_(x, y));
    }

    Stored<pixel_t> materialize() const {
        return img::core::materialize(*this);
    };

    template <typename G>
    Mapped<G, Mapped<F, I>> map(const G &fn) {
        return img::core::map(fn, *this);
    }

    Rectangle<coord_t> domain() const {
        return base_.domain();
    }

private:

    const F fn_;
    const I base_;

};

}}

#endif
