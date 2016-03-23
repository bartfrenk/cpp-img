#include "stored.hpp"
#include "mapped.hpp"
#include "lazy.hpp"

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
    auto plus = img::core::map([] (int x) { return x + 1; }, stored);
    auto plusplus = img::core::map(std::function<int(int)>(inc), plus);
    //auto zipped = img::core::zip(std::function<int(int, int)>(times), stored, mapped);
    //img::core::print(std::cout, zipped);
    return 1;
};
