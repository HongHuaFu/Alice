#pragma once
#include <PathTracingCPU/Vector.hpp>
#include <PathTracingCPU/Math.hpp>

namespace Alice::PathTracingCPU
{
    // 三维正交坐标系
    class Frame 
    {
    public:
        Vector3f s, t;
        Normal3f n;

        Frame() { }
        Frame(const Vector3f& s, const Vector3f& t, const Normal3f& n)
            : s(s), t(t), n(n) { }

        Frame(const Vector3f& x, const Vector3f& y, const Vector3f& z)
            : s(x), t(y), n(z) { }

        Frame(const Vector3f& n) : n(n) 
        {
            CoordinateSystem(n, s, t);
        }

        /// 世界空间到局部空间
        Vector3f ToLocal(const Vector3f& v) const 
        {
            return Vector3f(
                glm::dot(v,s), glm::dot(v,t), glm::dot(v,n)
            );
        }

        /// 局部空间到世界空间
        Vector3f ToWorld(const Vector3f& v) const 
        {
            return s * v.x + t * v.y + n * v.z;
        }

        // Assuming that the given direction is in the local coordinate
        // system, return the cosine of the angle between the normal and v 
        static float CosTheta(const Vector3f& v) 
        {
            return v.z;
        }

        // Assuming that the given direction is in the local coordinate
        // system, return the sine of the angle between the normal and v 
        static float SinTheta(const Vector3f& v) 
        {
            float temp = SinTheta2(v);
            if (temp <= 0.0f)
                return 0.0f;
            return std::sqrt(temp);
        }

        // brief Assuming that the given direction is in the local coordinate
        // system, return the tangent of the angle between the normal and v 
        static float TanTheta(const Vector3f& v) 
        {
            float temp = 1 - v.z * v.z;
            if (temp <= 0.0f)
                return 0.0f;
            return std::sqrt(temp) / v.z;
        }

        // Assuming that the given direction is in the local coordinate
        // system, return the squared sine of the angle between the normal and v 
        static float SinTheta2(const Vector3f& v) 
        {
            return 1.0f - v.z * v.z;
        }

        // brief Assuming that the given direction is in the local coordinate
        // system, return the sine of the phi parameter in spherical coordinates 
        static float SinPhi(const Vector3f& v) 
        {
            float sinTheta = Frame::SinTheta(v);
            if (sinTheta == 0.0f)
                return 1.0f;
            return glm::clamp(v.y / sinTheta, -1.0f, 1.0f);
        }

        // Assuming that the given direction is in the local coordinate
        // system, return the cosine of the phi parameter in spherical coordinates
        static float CosPhi(const Vector3f& v) 
        {
            float sinTheta = Frame::SinTheta(v);
            if (sinTheta == 0.0f)
                return 1.0f;
            return glm::clamp(v.x / sinTheta, -1.0f, 1.0f);
        }

        // Assuming that the given direction is in the local coordinate
        // system, return the squared sine of the phi parameter in  spherical
        // coordinates 
        static float SinPhi2(const Vector3f& v) 
        {
            return glm::clamp(v.y * v.y / SinTheta2(v), 0.0f, 1.0f);
        }

        // Assuming that the given direction is in the local coordinate
        // system, return the squared cosine of the phi parameter in  spherical
        // coordinates 
        static float CosPhi2(const Vector3f& v) 
        {
            return glm::clamp(v.x * v.x / SinTheta2(v), 0.0f, 1.0f);
        }

        bool operator==(const Frame& frame) const 
        {
            return frame.s == s && frame.t == t && frame.n == n;
        }

        bool operator!=(const Frame& frame) const 
        {
            return !operator==(frame);
        }
    };

    std::string ToString(const Frame& frame) 
    {
        return
            "Frame[  s = " + ToString(frame.s) +
            "  t = " + ToString(frame.t) +
            "  n = " + ToString(frame.n) +
            "]";
    }
}