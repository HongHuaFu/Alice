#pragma once
#include <RayTracingCPU/Shape.hpp>
#include <memory>

namespace Alice::RayTracingCPU
{
	class AABB;
	class Translate : public Shape 
	{
	public:
		Translate(std::shared_ptr<Shape> p, const vec3& displacement)
			: ptr(p), offset(displacement) {}

		virtual bool Intersect(const Ray& r, float t_min, float t_max, Hit& rec) const override;

		virtual bool GetBBox(float t0, float t1, AABB& output_box) const override;

	public:
		std::shared_ptr<Shape> ptr;
		vec3 offset;
	};

	class Rotate_Y : public Shape 
	{
	public:
		Rotate_Y(std::shared_ptr<Shape> p, float angle);

		virtual bool Intersect(const Ray& r, float t_min, float t_max, Hit& rec) const override;

		virtual bool GetBBox(float t0, float t1, AABB& output_box) const override;
		

		std::shared_ptr<Shape> ptr;
		float sin_theta;
		float cos_theta;
		bool hasbox;

		vec3 box_min;
		vec3 box_max;
	};
	
}