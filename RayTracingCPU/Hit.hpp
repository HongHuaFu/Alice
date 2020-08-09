#pragma once
#include <RayTracingCPU/Math.hpp>
#include <memory>

namespace Alice::RayTracingCPU
{
	class Material;
	// ���ڼ�¼���߻��еļ����������Ϣ
	class Hit
	{
	public:
		float t;
		vec3 pos;
		vec3 normal;
		vec2 uv;
		// bool front_face;
		std::shared_ptr<Material> material;
	};
}