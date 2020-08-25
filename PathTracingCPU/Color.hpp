#pragma once
#include <PathTracingCPU/Core.hpp>
#include <PathTracingCPU/Vector.hpp>

namespace Alice::PathTracingCPU 
{
    class Color3f
    {
    public:
        Vector3f color;

        /// Initialize the color vector with a uniform value
        Color3f(float value = 0.f) : color(value, value, value) { }

        /// Initialize the color vector with specific per-channel values
        Color3f(float r, float g, float b) : color(r, g, b) { }

        explicit Color3f(const Vector3f& c) : color(c) { }

        /// Return a reference to the red channel
        float& r() { return color.r; }

        /// Return a reference to the red channel (const version)
        const float& r() const { return color.r; }

        /// Return a reference to the green channel
        float& g() { return color.g; }

        /// Return a reference to the green channel (const version)
        const float& g() const { return color.g; }

        /// Return a reference to the blue channel
        float& b() { return color.b; }

        /// Return a reference to the blue channel (const version)
        const float& b() const { return color.b; }

        const Vector3f& GetColor() const { return color; }

        /// Clamp to the positive range
        Color3f Clamp() const 
        {
            return Color3f(std::max(r(), 0.0f), std::max(g(), 0.0f), std::max(b(), 0.0f));
        }

        /// Check if the color vector contains a NaN/Inf/negative value
        bool IsValid() const 
        {
            for (int i = 0; i < 3; ++i) {
                float value = color[i];
                if (value < 0 || !std::isfinite(value))
                    return false;
            }
            return true;
        }

        /// Convert from sRGB to linear RGB
        Color3f ToLinearRGB() const 
        {
            Color3f result;

            for (int i = 0; i < 3; ++i) {
                float value = color[i];

                if (value <= 0.04045f)
                    result.color[i] = value * (1.0f / 12.92f);
                else
                    result.color[i] = std::pow((value + 0.055f) * (1.0f / 1.055f), 2.4f);
            }

            return result;
        }

        /// Convert from linear RGB to sRGB
        Color3f ToSRGB() const 
        {
            Color3f result;

            for (int i = 0; i < 3; ++i) {
                float value = color[i];

                if (value <= 0.0031308f)
                    result.color[i] = 12.92f * value;
                else
                    result.color[i] = (1.0f + 0.055f) * std::pow(value, 1.0f / 2.4f) - 0.055f;
            }

            return result;
        }

        /// Return the associated luminance
        float GetLuminance() const 
        {
            return color[0] * 0.212671f + color[1] * 0.715160f + color[2] * 0.072169f;
        }
    };

    /// Return a human-readable string summary
    inline static std::string ToString(const Color3f& c)
    {
        return ToString(c.GetColor());
    }

    /// Represents a linear RGB color and a weight
    class Color4f 
    {
    public:
        Vector4f color;

        const Vector4f& GetColor() const { return color; }

        /// Create an zero value
        Color4f() : color(0.0f, 0.0f, 0.0f, 0.0f) { }

        /// Create from a 3-channel color
        Color4f(const Color3f& c) : color(c.r(), c.g(), c.b(), 1.0f) { }

        /// Initialize the color vector with specific per-channel values
        Color4f(float r, float g, float b, float w) : color(r, g, b, w) { }

        explicit Color4f(const Vector4f& v) : color(v) { }

        /// Divide by the filter weight and convert into a Color3f value
        Color3f DivideByFilterWeight() const 
        {
            Vector3f res;
            if (color.w != 0)
                res = Vector3f(color.x,color.y,color.z) / color.w;
            else
                res = Vector3f(0.0f);
            return Color3f(res);
        }
    };

    /// Return a human-readable string summary
    inline static std::string ToString(const Color4f& c)
    {
        return ToString(c.GetColor());
    }
}