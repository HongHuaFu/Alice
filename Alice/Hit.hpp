#pragma once
#include <Math.hpp>
#include <memory>

namespace Alice
{
	class Material;
	// ���ڼ�¼���߻��еļ����������Ϣ
	class Hit
	{
	public:
		float t;
		vec3 pos;
		vec3 normal;
		std::shared_ptr<Material> material;
	};
}