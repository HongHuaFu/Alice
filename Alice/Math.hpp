#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <glm/gtc/random.hpp>
#include <algorithm>

namespace Alice
{
	using namespace glm;
	
	// ÕÛÉäº¯Êý
	bool Refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) 
	{
		vec3 uv = normalize(v);
		float dt = dot(uv, n);
		float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);
		if (discriminant > 0) {
			refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
			return true;
		}
		else
			return false;
	}

	// Schlick½üËÆ
	float Schlick(float cosine, float ref_idx) 
	{
		float r0 = (1 - ref_idx) / (1 + ref_idx);
		r0 = r0*r0;
		return r0 + (1-r0)*pow((1 - cosine),5);
	}
}