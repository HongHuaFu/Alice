#pragma once
#include <Math.hpp>
#include <Shape.hpp>

namespace Alice
{
	class Hit
	{
	public:
		float tNear;
		uint32_t index;
		glm::vec2 uv;
		Shape* hitShape;
	};
}