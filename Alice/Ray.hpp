#pragma once
#include <Math.hpp>

namespace Alice
{
	class Ray
	{
	public:
		glm::vec3 origin;
		glm::vec3 direction,direction_inv;
		float t = 0.0f;
		float t_min = 0.0f;
		float t_max = std::numeric_limits<float>::max();
	public:
		Ray(const glm::vec3& ori, const glm::vec3& dir, const float _t = 0.0f)
		: origin(ori), direction(dir),t(_t) 
		{
			direction_inv = glm::vec3(1.0f/direction.x, 1.0f/direction.y, 1.0f/direction.z);
		}

		auto operator()(float t) const { return origin + direction * t; }
	};
}