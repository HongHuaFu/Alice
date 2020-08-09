#pragma once
#include <RayTracingCPU/Math.hpp>
#include <memory>

namespace Alice::RayTracingCPU
{
	class Material;
	// 用于记录光线击中的几何体表面信息
	class Hit
	{
	public:
		float t;
		vec3 pos;
		vec3 normal;
		std::shared_ptr<Material> material;
	};
}