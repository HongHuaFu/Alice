#pragma once
#include <PathTracingCPU/Core.hpp>
#include <PathTracingCPU/Vector.hpp>

namespace Alice::PathTracingCPU 
{
    class Color3f
    {
    public:
        Vector3f color;

        Color3f(float value = 0.f) : color(value, value, value) { }
        Color3f(float r, float g, float b) : color(r, g, b) { }
        explicit Color3f(const Vector3f& c) : color(c) { }

        float& r() { return color.r; }
        const float& r() const { return color.r; }
        float& g() { return color.g; }
        const float& g() const { return color.g; }
        float& b() { return color.b; }
        const float& b() const { return color.b; }
        const Vector3f& GetColor() const { return color; }

        /// 颜色值限定在正值
        Color3f Clamp() const 
        {
            return Color3f(std::max(r(), 0.0f), std::max(g(), 0.0f), std::max(b(), 0.0f));
        }

        /// 判断颜色值是否有效 （非负，非无穷，非NaN）
        bool IsValid() const 
        {
            for (int i = 0; i < 3; ++i) {
                float value = color[i];
                if (value < 0 || !std::isfinite(value))
                    return false;
            }
            return true;
        }

        /// sRGB 转换到线性空间
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

        /// 线性空间转换到sRGB
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

        /// 转换为灰度（亮度）
        float GetLuminance() const 
        {
            return color[0] * 0.212671f + color[1] * 0.715160f + color[2] * 0.072169f;
        }
    };

    inline static std::string ToString(const Color3f& c)
    {
        return ToString(c.GetColor());
    }

    /// RGB 与一个权重通道
    class Color4f 
    {
    public:
        Vector4f color;

        const Vector4f& GetColor() const { return color; }
        Color4f() : color(0.0f, 0.0f, 0.0f, 0.0f) { }
        Color4f(const Color3f& c) : color(c.r(), c.g(), c.b(), 1.0f) { }
        Color4f(float r, float g, float b, float w) : color(r, g, b, w) { }
        explicit Color4f(const Vector4f& v) : color(v) { }

        /// /w 操作并返回rgb
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

    inline static std::string ToString(const Color4f& c)
    {
        return ToString(c.GetColor());
    }
}