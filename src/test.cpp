#include "stored.hpp"
#include "free_image.hpp"

#include "mapped.hpp"
#include "zipped.hpp"
#include "utils.hpp"
#include "operators.hpp"

#include <functional>
#include <iostream>

using namespace img::core;
using img::utils::print;
using img::backend::FreeImage;

uint8_t clip(const int x) {
    if (x > 0xFF) return 0xFF;
    if (x < 0) return 0;
    return (uint8_t) (x & 0xFF);
}

int main() {
    FreeImage_Initialise();

    FreeImage<uint8_t> dice(FIF_BMP, "data/dice.bmp");
    auto result = (dice + dice).map([](int x) { return x - 128; }).map(&clip);
    materialize<FreeImage>(result).save(FIF_BMP, "double_dice.bmp");

    FreeImage_DeInitialise();
    return 0;
};
