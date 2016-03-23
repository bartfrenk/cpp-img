#ifndef ZIPPED_HPP
#define ZIPPED_HPP

#include <functional>
#include "lazy.hpp"

namespace img {
namespace core {

template <typename I, typename J, typename P>
class Zipped {
public:
    using pixel_t = P;
    using coord_t = typename I::coord_t;
    using function_t = std::function<pixel_t(typename I::pixel_t, typename J::pixel_t)>;

    Zipped(const function_t &fn, const I &base1, const J &base2) :
        fn_(fn), base1_(base1), base2_(base2)
    {
        if (base1_.domain() != base2_.domain()) {};
    };

    pixel_t operator()(const coord_t x, const coord_t y) const {
        return fn_(base1_(x, y), base2_(x, y));
    }

    /** Evaluate image and return stored result. */
    Stored<coord_t, pixel_t> materialize() const {
        return img::core::materialize(*this);
    };

    Rectangle<coord_t> domain() const {
        return base1_.domain();
    }
private:

    const function_t fn_;
    const I base1_;
    const J base2_;

};

template <typename I, typename J, typename P>
Zipped<I, J, P> zip(const std::function<P(typename I::pixel_t, typename J::pixel_t)> &fn,
                    const I &base1, const J &base2)
{
    return Zipped<I, J, P>(fn, base1, base2);
};

}}

#endif
