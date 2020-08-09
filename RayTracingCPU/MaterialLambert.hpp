#pragma once
#include <RayTracingCPU/Random.hpp>
#include <RayTracingCPU/Material.hpp>
#include <RayTracingCPU/Texture.hpp>

namespace Alice::RayTracingCPU
{
	class MaterialLambert: public Material
	{
	private:
		std::shared_ptr<Texture> albedo;
	public:
		MaterialLambert(const vec3& a = vec3(0)) : albedo(std::make_shared<TextureSolidColor>(a)){ }

		MaterialLambert(std::shared_ptr<Texture> a) : albedo(a) { }

		bool Scatter(const Ray& r_in,const Hit& hit,vec3& attenuation,Ray& scattered) const override
		{
			// ÀÊª˙¬˛∑¥…‰
			vec3 target = hit.pos + hit.normal + Random::GetRandom3dUint();

			scattered = Ray(hit.pos, target - hit.pos,r_in.GetTime());
			attenuation = albedo->Color(hit.uv.x,hit.uv.y,hit.pos);

			// Lambert ”¿‘∂∑¥…‰
			return true;
		}
	};
}