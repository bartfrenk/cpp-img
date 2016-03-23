#include "stored.hpp"
#include "mapped.hpp"
#include "zipped.hpp"
#include "utils.hpp"
#include "nearest_neighbor.hpp"

#include <functional>
#include <iostream>

using namespace img::core;

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
    Stored<size_t, int> stored(10, 10);
    auto mapped = map([] (int x) { return x + 1; }, stored);
    auto zipped = zip([] (int x, int y) { return (x + 1) * y + 1; }, stored, mapped);
    auto z = zipped.map([](int x) { return x * 2; });
    auto u = mapped.map([](int x) { return 3 + x; }).map([](int x) { return x + 1; }).materialize();
    u(2, 2) = 9;
    print(std::cout, u);
    auto interp = nearest_neighbor<double>(u);
    std::cout << interp(1.3, 1.3) << " " << interp.map([](int x) { return 2 * x; })(1.7, 1.7)
              << std::endl;
    return 0;
};
