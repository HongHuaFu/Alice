#pragma once
#include <RayTracingCPU/Math.hpp>
#include <RayTracingCPU/Shape.hpp>
#include <RayTracingCPU/Ray.hpp>
#include <iostream>

namespace Alice::RayTracingCPU
{
	class AABB
	{
	public:
		AABB() = default;
		AABB(const vec3& a,const vec3& b) : min(a),max(b){ }

		vec3 GetMin() const { return min; }
		vec3 GetMax() const { return max; }

		bool Intersect(const Ray& r,float tmin,float tmax) const
		{
			for (int a = 0; a < 3; a++) {
				auto invD = 1.0f / r.GetDirection()[a];
				auto t0 = (min[a] - r.GetOrigin()[a]) * invD;
				auto t1 = (max[a] - r.GetOrigin()[a]) * invD;
				if (invD < 0.0f)
					std::swap(t0, t1);
				tmin = t0 > tmin ? t0 : tmin;
				tmax = t1 < tmax ? t1 : tmax;
				if (tmax <= tmin)
					return false;
			}
			return true;
		}

	protected:
		vec3 min;
		vec3 max;
	};

	inline AABB SurroundingBox(AABB box0, AABB box1) 
	{
		vec3 small(fmin(box0.GetMin().x, box1.GetMin().x),
			fmin(box0.GetMin().y, box1.GetMin().y),
			fmin(box0.GetMin().z, box1.GetMin().z));

		vec3 big(fmax(box0.GetMax().x, box1.GetMax().x),
			fmax(box0.GetMax().y, box1.GetMax().y),
			fmax(box0.GetMax().z, box1.GetMax().z));

		return AABB(small,big);
	}

	inline bool BBoxCompare(const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b, int axis) 
	{
		AABB box_a;
		AABB box_b;

		if (!a->GetBBox(0,0, box_a) || !b->GetBBox(0,0, box_b))
			std::cerr << "No bounding box in bvh_node constructor.\n";

		return box_a.GetMin()[axis] < box_b.GetMin()[axis];
	}

	inline bool BBox_X_Compare (const std::shared_ptr<Shape> a, const std::shared_ptr<Shape> b) 
	{
		return BBoxCompare(a, b, 0);
	}

	inline bool BBox_Y_Compare (const std::shared_ptr<Shape> a, const  std::shared_ptr<Shape> b) 
	{
		return BBoxCompare(a, b, 1);
	}

	inline bool BBox_Z_Compare (const std::shared_ptr<Shape> a, const  std::shared_ptr<Shape> b) 
	{
		return BBoxCompare(a, b, 2);
	}
}