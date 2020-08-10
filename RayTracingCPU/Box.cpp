#include <RayTracingCPU/Box.hpp>
#include <RayTracingCPU/Scene.hpp>
#include <RayTracingCPU/AABB.hpp>
#include <RayTracingCPU/AABBRect.hpp>

namespace Alice::RayTracingCPU
{
	Box::Box(const vec3& p0,const vec3& p1,std::shared_ptr<Material> ptr)
	{
		box_min = p0;
		box_max = p1;
		sides = std::make_shared<Scene>();
		sides->AddShapePtrRef(std::make_shared<AABB_Rect_XY>(p0.x, p1.x, p0.y, p1.y, p1.z, ptr));
		sides->AddShapePtrRef(std::make_shared<AABB_Rect_XY>(p0.x, p1.x, p0.y, p1.y, p0.z, ptr));

		sides->AddShapePtrRef(std::make_shared<AABB_Rect_XZ>(p0.x, p1.x, p0.z, p1.z, p1.y, ptr));
		sides->AddShapePtrRef(std::make_shared<AABB_Rect_XZ>(p0.x, p1.x, p0.z, p1.z, p0.y, ptr));

		sides->AddShapePtrRef(std::make_shared<AABB_Rect_YZ>(p0.y, p1.y, p0.z, p1.z, p1.x, ptr));
		sides->AddShapePtrRef(std::make_shared<AABB_Rect_YZ>(p0.y, p1.y, p0.z, p1.z, p0.x, ptr));
	}

	bool Box::Intersect(const Ray& r,float t0,float t1,Hit& hit) const
	{
		return sides->RayTrace(r,t0,t1,hit);
	}

	bool Box::GetBBox(float t0, float t1, AABB& output_box) const
	{
		output_box = AABB(box_min, box_max);
		return true;
	}
}