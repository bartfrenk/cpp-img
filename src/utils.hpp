#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <functional>

namespace img {
namespace utils {

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
