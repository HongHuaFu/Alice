#pragma once
#include <RayTracingCPU/Shape.hpp>
#include <vector>
#include <memory>
#include <RayTracingCPU/Material.hpp>

namespace Alice::RayTracingCPU
{
	class Scene;
	class Box: public Shape
	{
	public:
		Box() {}
		Box(const vec3& p0,const vec3& p1,std::shared_ptr<Material> ptr);
		

		virtual bool Intersect(const Ray& r,float t0,float t1,Hit& hit) const override;

		virtual bool GetBBox(float t0, float t1, AABB& output_box) const override;

	public:
		vec3 box_min;
		vec3 box_max;
		std::shared_ptr<Scene> sides;
	};
}