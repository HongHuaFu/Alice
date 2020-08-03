#pragma once
#include <Math.hpp>
#include <Material.hpp>

namespace Alice
{
	// 用于记录光线击中的几何体表面信息
	class Hit
	{
	public:
		float t;
		vec3 pos;
		vec3 normal;
		Material* material;
	};
}