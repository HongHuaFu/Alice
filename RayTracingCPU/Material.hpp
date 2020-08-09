#pragma once
#include <RayTracingCPU/Math.hpp>
#include <RayTracingCPU/Ray.hpp>
#include <RayTracingCPU/Hit.hpp>
#include <RayTracingCPU/Texture.hpp>

namespace Alice::RayTracingCPU
{
	class Material
	{
	public:
		virtual bool Scatter(const Ray&,const Hit&, vec3&, Ray&) const = 0;
		// ×Ô·¢¹â
		virtual vec3 Emitted(float u, float v, const vec3& p) const 
		{
			return vec3(0,0,0); 
		}
	};

	class MaterialDiffuseLight : public Material  
	{
	public:
		MaterialDiffuseLight(std::shared_ptr<Texture> a) : emit(a) {}
		MaterialDiffuseLight(vec3 c) : emit(std::make_shared<TextureSolidColor>(c)) {}

		virtual bool Scatter(const Ray& r_in, const Hit& rec, vec3& attenuation, Ray& scattered) const override 
		{
			return false;
		}

		virtual vec3 Emitted(float u, float v, const vec3& p) const override 
		{
			return emit->Color(u, v, p);
		}

	public:
		std::shared_ptr<Texture> emit;
	};
}
