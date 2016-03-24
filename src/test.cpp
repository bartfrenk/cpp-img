#include "stored.hpp"
#include "mapped.hpp"
#include "zipped.hpp"
#include "utils.hpp"
#include "operators.hpp"
#include "nearest_neighbor.hpp"

#include <functional>
#include <iostream>

using namespace img::core;
using img::utils::print;

int inc(const int x) {
    return x + 1;
}

int main() {
    Stored<size_t, int> stored(10, 10);
    stored(0, 0) = 1;
    auto result = (stored + map(&inc, stored)) * map(&inc, map(&inc, stored));
    print(std::cout, result);
    auto interp = nearest_neighbor<double>(result);
    std::cout << interp(1.3, 1.3) << " " << interp.map([](int x) { return 2 * x; })(1.7, 1.7)
              << std::endl;
    return 0;
};
