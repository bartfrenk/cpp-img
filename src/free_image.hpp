#ifndef FREE_IMAGE_HPP
#define FREE_IMAGE_HPP

#include <FreeImage.h>
#include <string>
#include <memory>
#include <climits>

#include "orthotope.hpp"


namespace img {
namespace backend {

// TODO: think about memory management here!

namespace {

struct FreeImageDeleter {
    void operator()(FIBITMAP * ptr)
    {
        if (ptr != nullptr)
            FreeImage_Unload(ptr);
    }
};

}

template <typename P>
class FreeImage {
public:
    using coord_t = size_t;
    using pixel_t = P;

    FreeImage(const size_t width, const size_t height)
        : FreeImage(FreeImage_Allocate(width, height, CHAR_BIT * sizeof(pixel_t))) {};

    FreeImage(const FREE_IMAGE_FORMAT fif, const std::string path)
        : FreeImage(FreeImage_Load(fif, path.c_str())) {};

    void save(const FREE_IMAGE_FORMAT fif, const std::string path) const {
        FreeImage_Save(fif, bitmap_.get(), path.c_str());
    }

    pixel_t& operator()(const coord_t x, const coord_t y) {
        BYTE *buffer = (BYTE *) FreeImage_GetBits(bitmap_.get());
        return *reinterpret_cast<pixel_t*>(buffer + index(x, y));
    }

    pixel_t operator()(const coord_t x, const coord_t y) const {
        BYTE *buffer = (BYTE *) FreeImage_GetBits(bitmap_.get());
        return *reinterpret_cast<pixel_t*>(buffer + index(x, y));
    }

    Rectangle<coord_t> domain() const {
        return domain_;
    }

private:
    FreeImage(FIBITMAP * const bitmap)
        // TODO: add error checking
        : bitmap_(bitmap, FreeImageDeleter()),
          domain_(FreeImage_GetWidth(bitmap), FreeImage_GetHeight(bitmap)),
          pitch_(FreeImage_GetPitch(bitmap)) {};

    inline size_t index(const coord_t x, const coord_t y) const {
        return y * pitch_ + sizeof(pixel_t) * x;
    }

    std::shared_ptr<FIBITMAP> bitmap_;
    const Rectangle<coord_t> domain_;
    const coord_t pitch_;
};

}}

#endif
