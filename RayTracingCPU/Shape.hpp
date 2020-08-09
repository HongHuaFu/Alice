#pragma once
#include <RayTracingCPU/Math.hpp>

namespace Alice::RayTracingCPU
{
	class Hit;
	class Ray;
	class AABB;

	// 基础的形状类
	// 所有其他可渲染几何体均继承自它
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		virtual bool Intersect(const Ray& r,float t_min, float t_max, Hit& hit) const = 0;
		virtual bool GetBBox(float t0, float t1, AABB& output_box) const = 0;
	};
}