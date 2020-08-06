#pragma once
#include <Math.hpp>

namespace Alice
{
	class Ray
	{
	private:
		vec3 origin;
		vec3 direction;
	public:
		Ray() = default;
		Ray(const vec3& orig,const vec3& dir):origin(orig),direction(dir){ }

		vec3 At(float t) const { return origin + t * direction; }
		vec3 GetOrigin() const { return origin; }
		vec3 GetDirection() const { return direction; }
		void SetOrigin(const vec3& orig) { origin = orig; }
		void SetDirection(const vec3& dir) { direction = dir; }
	};
}