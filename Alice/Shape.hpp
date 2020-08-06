#pragma once
#include <Math.hpp>
#include <Ray.hpp>
#include <Hit.hpp>

namespace Alice
{
	// 基础的形状类
	// 所有其他可渲染几何体均继承自它
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		virtual bool Intersect(const Ray& r,float t_min, float t_max, Hit& hit) const = 0;
	};
}