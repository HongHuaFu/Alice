#pragma once
#include <Math.hpp>

namespace Alice
{
	class AABB;
	class Hit;
	class Ray;
	// ��������״��
	// ������������Ⱦ��������̳�����
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		virtual bool Intersect(const Ray& r,float t_min, float t_max, Hit& hit) const = 0;
		virtual bool GetBBox(float t0, float t1, AABB& output_box) const = 0;
	};
}