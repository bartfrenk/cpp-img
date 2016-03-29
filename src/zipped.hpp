#ifndef ZIPPED_HPP
#define ZIPPED_HPP

#include <functional>
#include <type_traits>

#include "orthotope.hpp"
#include "stored.hpp"
#include "mapped.hpp"
#include "utils.hpp"

namespace img {
namespace core {

template <typename F, typename I, typename J>
class Zipped {
public:
    using pixel_t = typename std::result_of<F(typename I::pixel_t, typename J::pixel_t)>::type;
    using coord_t = typename I::coord_t;

    Zipped(const F &fn, const I &base1, const J &base2) :
        fn_(fn), base1_(base1), base2_(base2)
    {
        if (base1_.domain() != base2_.domain()) {};
    };

    pixel_t operator()(const coord_t x, const coord_t y) const {
        return fn_(base1_(x, y), base2_(x, y));
    }

    /** Evaluate image and return stored result. */
    Stored<pixel_t> materialize() const {
        return img::core::materialize(*this);
    };

    template <typename G>
    Mapped<G, Zipped<F, I, J>> map(const G &fn) {
        return img::core::map(fn, *this);
    }

    Rectangle<coord_t> domain() const {
        return base1_.domain();
    }
private:

    const F fn_;
    const I base1_;
    const J base2_;

};

template <typename F, typename I, typename J>
Zipped<F, I, J> zip(const F &fn, const I &base1, const J &base2) {
    return Zipped<F, I, J>(fn, base1, base2);
};


}}

#endif
