#include "stored.hpp"
#include "mapped.hpp"
#include "zipped.hpp"
#include "utils.hpp"

#include <functional>
#include <iostream>

int inc(const int x) {
    return x + 1;
}

int plus(const int v, const int w) {
    return v + w;
}

int times(const int v, const int w) {
    return v * w;
}

int main() {
    img::core::Stored<size_t, int> stored(10, 10);
    auto mapped = img::core::map([] (int x) { return x + 1; }, stored);
    auto zipped = img::core::zip([] (int x, int y) { return (x + 1) * y + 1; }, stored, mapped);
    img::core::print(std::cout, zipped);
    return 0;
};
