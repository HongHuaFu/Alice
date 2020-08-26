#pragma once
#include <PathTracingCPU/Vector.hpp>
#include <PathTracingCPU/Frame.hpp>
#include <PathTracingCPU/Core.hpp>

namespace Alice::PathTracingCPU 
{
    class Mesh;
    class Intersection 
    {
    public:
        /// Position of the surface intersection
        Point3f p;
        /// Unoccluded distance along the ray
        float t;
        /// UV coordinates, if any
        Point2f uv;
        /// Shading frame (based on the shading normal)
        Frame shFrame;
        /// Geometric frame (based on the true geometry)
        Frame geoFrame;
        /// Pointer to the associated mesh
        const Ref<Mesh> mesh;

        /// Create an uninitialized intersection record
        Intersection() : mesh(nullptr) { }

        /// Transform a direction vector into the local shading frame
        Vector3f ToLocal(const Vector3f& d) const 
        {
            return shFrame.ToLocal(d);
        }

        /// Transform a direction vector from local to world coordinates
        Vector3f ToWorld(const Vector3f& d) const {
            return shFrame.ToWorld(d);
        }

        /// Return a human-readable summary of the intersection record
        std::string toString() const;
    };
}