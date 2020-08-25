#pragma once
#include <PathTracingCPU/Color.hpp>
#include <PathTracingCPU/Vector.hpp>

namespace Alice::PathTracingCPU
{
    enum class BitmapType
    {
        PNG,
        JPG,
        TGA
    };

    class Texture 
    {
    public:
        std::vector<Color3f> colorData = {0}; // Range 0 - 1
        Vector2i size = {0,0};

        /// Allocate a new texture of specified size.
        Texture(const Vector2i& s = Vector2i(0, 0))
            : size(s)
        {
            colorData.resize(static_cast<size_t>(s.x) * static_cast<size_t>(s.y));
            colorData.clear();
        }

        /// Load an bitmap file with the specified filename
        Texture(const std::string& filename);

        /// Save the bitmap.
        void Save(const std::string& filename, BitmapType type);
    };
}