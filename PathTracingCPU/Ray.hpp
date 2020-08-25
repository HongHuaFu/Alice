#pragma once
#include <PathTracingCPU/Core.hpp>

namespace Alice::PathTracingCPU 
{
    template <typename PointType, typename VectorType> 
    class TRay 
    {
    public:
        typedef typename PointType::value_type  Scalar;

        // Ray origin.
        PointType o;     
        // Ray direction.
        VectorType d;    
        // Componentwise reciprocals of the ray direction.
        VectorType dRcp; 

        // Minimum position on the ray segment.
        Scalar mint;  
        // Maximum position on the ray segment.
        Scalar maxt;   

        /// Construct a new ray.
        TRay() : mint(Epsilon),
            maxt(std::numeric_limits<Scalar>::infinity()) { }

        /// Construct a new ray.
        TRay(const PointType& o, const VectorType& d) : o(o), d(d),
            mint(Epsilon), maxt(std::numeric_limits<Scalar>::infinity()) 
        {
            Update();
        }

        /// Construct a new ray.
        TRay(const PointType& o, const VectorType& d,
            Scalar mint, Scalar maxt) : o(o), d(d), mint(mint), maxt(maxt) 
        {
            Update();
        }

        /// Copy constructor.
        TRay(const TRay& ray)
            : o(ray.o), d(ray.d), dRcp(ray.dRcp),
            mint(ray.mint), maxt(ray.maxt) { }

        /// Copy a ray, but change the covered segment of the copy.
        TRay(const TRay& ray, Scalar mint, Scalar maxt)
            : o(ray.o), d(ray.d), dRcp(ray.dRcp), mint(mint), maxt(maxt) { }

        // Update the reciprocal ray directions after changing 'd'.
        void Update() 
        {
            dRcp = Inverse(d);
        }

        // Return the position of a point along the ray.
        PointType operator() (Scalar t) const { return o + t * d; }

        // Return a ray that points into the opposite direction.
        TRay reverse() const 
        {
            TRay result;
            result.o = o; 
            result.d = -d; 
            result.dRcp = -dRcp;
            result.mint = mint; 
            result.maxt = maxt;
            return result;
        }
    };

    template <typename PointType, typename VectorType>
    inline static std::string ToString(const TRay<PointType, VectorType>& r) 
    {
        return
            "Ray[ o = " + ToString(r.o) + ", d = " + ToString(r.d) +
            ", mint = " + ToString(r.mint) + ", maxt = " + ToString(r.maxt);
    }

    using Ray2f = TRay<Point2f, Vector2f>;
    using Ray3f = TRay<Point3f, Vector3f>;
}