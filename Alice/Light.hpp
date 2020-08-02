#pragma once
#include <Math.hpp>

namespace Alice
{
	class Light
	{
	protected:
		glm::vec3 position;
		glm::vec3 intensity;

	public:
		Light(const glm::vec3& p, const glm::vec3& i): position(p), intensity(i){ }
		virtual ~Light() = default;

		auto GetPosition() const { return position; }
		auto GetIntensity() const { return intensity; }
		auto SetPosition(const glm::vec3& pos) { position = pos; }
		auto SetIntensity(const glm::vec3& inten) { intensity = inten; }
	};
}