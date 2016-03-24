#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <functional>

namespace img {
namespace utils {

template<class F>
struct function_traits;

// function pointer
template<class R, class... Args>
struct function_traits<R(*)(Args...)> : public function_traits<R(Args...)>
{};

template<class R, class... Args>
struct function_traits<R(Args...)> {
    using return_type = R;

    static constexpr std::size_t arity = sizeof...(Args);

    template <std::size_t N>
    struct argument
    {
        static_assert(N < arity, "error: invalid parameter index");
        using type = typename std::tuple_element<N, std::tuple<Args...>>::type;
    };
};


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
