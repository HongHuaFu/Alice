#pragma once
#include <RayTracingCPU/Math.hpp>
#include <RayTracingCPU/Ray.hpp>
#include <RayTracingCPU/Hit.hpp>

namespace Alice::RayTracingCPU
{
	class Material
	{
	public:
		virtual bool Scatter(const Ray&,const Hit&, vec3&, Ray&) const = 0;
	};
}
