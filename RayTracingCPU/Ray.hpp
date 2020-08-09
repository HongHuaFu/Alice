#pragma once
#include <RayTracingCPU/Math.hpp>

namespace Alice::RayTracingCPU
{
	class Ray
	{
	private:
		vec3 origin;
		vec3 direction;
		// 时间变量 用于运动模糊
		float time;
	public:
		Ray() = default;
		Ray(const vec3& orig,const vec3& dir,float time = 0):origin(orig),direction(dir),time(time){ }

		vec3 At(float t) const { return origin + t * direction; }
		vec3 GetOrigin() const { return origin; }
		vec3 GetDirection() const { return direction; }
		void SetOrigin(const vec3& orig) { origin = orig; }
		void SetDirection(const vec3& dir) { direction = dir; }

		float GetTime() const { return time; }
		void SetTime(float t) { time = t; }
	};
}