#pragma once
#include <Math.hpp>
#include <Material.hpp>

namespace Alice
{
	// ���ڼ�¼���߻��еļ����������Ϣ
	class Hit
	{
	public:
		float t;
		vec3 pos;
		vec3 normal;
		Material* material;
	};
}