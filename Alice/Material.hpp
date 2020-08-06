#pragma once
#include <Math.hpp>
#include <Ray.hpp>
#include <Hit.hpp>

namespace Alice
{
	class Material
	{
	public:
		virtual bool Scatter(const Ray&,const Hit&, vec3&, Ray&) const = 0;
	};
}
