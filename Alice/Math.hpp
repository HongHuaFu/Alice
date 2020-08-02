#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/compatibility.hpp>
#include <algorithm>

namespace Alice
{
	// Refraction direction using Snell's law
	// If the ray is outside need to make cosi positive cosi = -N.I
	// If the ray is inside need to invert the refractive indices and negate the normal N
	inline glm::vec3 Refract(const glm::vec3 &I, const glm::vec3 &N, const float &ior)
	{
		float cosi = glm::clamp(-1.0f, 1.0f, glm::dot(I, N));
		float etai = 1, etat = ior;
		glm::vec3 n = N;
		if (cosi < 0) { cosi = -cosi; } else { std::swap(etai, etat); n= -N; }
		float eta = etai / etat;
		float k = 1 - eta * eta * (1 - cosi * cosi);
		return k < 0 ? glm::vec3(0) : eta * I + (eta * cosi - sqrtf(k)) * n;
	}

	// Fresnel snell
	inline float Fresnel(const glm::vec3& viewDir, const glm::vec3& N, const float& ior)
	{
		float cosi = glm::clamp(-1.0f, 1.0f, glm::dot(viewDir, N));
		float etai = 1.0f, etat = ior;
		if (cosi > 0) {  std::swap(etai, etat); }
		// Compute sini using Snell's law
		float sint = etai / etat * sqrtf(std::max(0.f, 1 - cosi * cosi));
		// Total internal reflection
		if (sint >= 1) 
		{
			return 1;
		}
		else 
		{
			float cost = sqrtf(std::max(0.f, 1 - sint * sint));
			cosi = fabsf(cosi);
			float Rs = ((etat * cosi) - (etai * cost)) / ((etat * cosi) + (etai * cost));
			float Rp = ((etai * cosi) - (etat * cost)) / ((etai * cosi) + (etat * cost));
			return (Rs * Rs + Rp * Rp) / 2;
		}
		// As a consequence of the conservation of energy, transmittance is given by:
		// kt = 1 - kr;
	}

	inline bool SolveQuadratic(const float& a,const float& b,const float& c,float& x0,float& x1)
	{
		float discr = b * b - 4 * a * c;
		if (discr < 0)
			return false;
		else if (discr == 0)
			x0 = x1 = -0.5 * b / a;
		else
		{
			float q = (b > 0) ? -0.5f * (b + sqrt(discr)) : -0.5f * (b - sqrt(discr));
			x0 = q / a;
			x1 = c / q;
		}
		if (x0 > x1)
			std::swap(x0, x1);
		return true;
	}
}