#pragma once
#include <Random.hpp>

namespace Alice
{
	class MaterialLambert: public Material
	{
	private:
		vec3 albedo;
	public:
		MaterialLambert(const vec3& a = vec3(0)) : albedo(a){ }

		bool Scatter(const Ray& r_in,const Hit& hit,vec3& attenuation,Ray& scattered) const override
		{
			// Ëæ»úÂş·´Éä
			vec3 target = hit.pos + hit.normal + Random::GetRandom3dUint();

			scattered = Ray(hit.pos, target - hit.pos);
			attenuation = albedo;

			// Lambert ÓÀÔ¶·´Éä
			return true;
		}
	};
}