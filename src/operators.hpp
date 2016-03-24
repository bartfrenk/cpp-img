#ifndef OPERATORS_HPP
#define OPERATORS_HPP

#include <type_traits>
#include <functional>
#include "zipped.hpp"
#include "utils.hpp"

namespace {

template <typename P, typename Q>
auto plus(const P p, const Q q) -> decltype(p + q) {
    return p + q;
}

template <typename P, typename Q>
auto times(const P p, const Q q) -> decltype(p * q) {
    return p * q;
}

}

namespace img {
namespace core {

template <typename I, typename J>
auto operator+(const I &first, const J &second)
    -> decltype(img::core::zip(&plus<typename I::pixel_t, typename J::pixel_t>,
                               first, second))
{
    return img::core::zip(&plus<typename I::pixel_t, typename J::pixel_t>,
                          first, second);
}

template <typename I, typename J>
auto operator*(const I &first, const J &second)
    -> decltype(img::core::zip(&times<typename I::pixel_t, typename J::pixel_t>,
                               first, second))
{
    return img::core::zip(&times<typename I::pixel_t, typename J::pixel_t>,
                          first, second);
}


}}

#endif
