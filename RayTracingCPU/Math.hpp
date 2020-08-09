#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/random.hpp>
#include <algorithm>

namespace Alice::RayTracingCPU
{
	using namespace glm;
	
	// 折射函数
	inline bool Refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) 
	{
		vec3 uv = normalize(v);
		float dt = dot(uv, n);
		float discriminant = 1.0f - ni_over_nt*ni_over_nt*(1.0f - dt*dt);
		if (discriminant > 0) 
		{
			refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
			return true;
		}
		else
			return false;
	}

	// Schlick近似
	inline float Schlick(float cosine, float ref_idx) 
	{
		float r0 = (1 - ref_idx) / (1 + ref_idx);
			  r0 = r0*r0;
		return r0 + (1-r0)*pow((1 - cosine),5);
	}

	// 计算球形UV
	inline vec2 SphereUV(const vec3& p) 
	{
		auto phi = atan2(p.z, p.x);
		auto theta = asin(p.y);
		vec2 res;
		res.x = 1-(phi + pi<float>()) / (2*pi<float>());
		res.y = (theta + pi<float>() * 0.5f) / pi<float>();
		return res;
	}
}