#pragma once
#include <Math.hpp>
#include <Ray.hpp>
#include <Hit.hpp>

namespace Alice
{
	// ��������״��
	// ������������Ⱦ��������̳�����
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		virtual bool Intersect(const Ray& r,float t_min, float t_max, Hit& hit) const = 0;
	};
}