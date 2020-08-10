#pragma once
#include <RayTracingCPU/Shape.hpp>
#include <RayTracingCPU/Material.hpp>
#include <RayTracingCPU/Texture.hpp>
#include <RayTracingCPU/Random.hpp>

namespace Alice::RayTracingCPU
{
	class MaterialIsotropic : public Material 
	{
	public:
		MaterialIsotropic(std::shared_ptr<Texture> a) : albedo(a) {}
		MaterialIsotropic(vec3 a) : albedo(std::make_shared<TextureSolidColor>(a)) {}
		virtual bool Scatter(const Ray& r_in, const Hit& rec, vec3& attenuation, Ray& scattered) const  
		{
			scattered = Ray(rec.pos, Random::GetRandom3dUint(), r_in.GetTime());
			attenuation = albedo->Color(rec.uv.x, rec.uv.y, rec.pos);
			return true;
		}
		std::shared_ptr<Texture> albedo;
	};

	class Medium_Constant : public Shape 
	{
	public:
		Medium_Constant(std::shared_ptr<Shape> b, float d, std::shared_ptr<Texture> a)
			: boundary(b),neg_inv_density(-1/d),phase_function(std::make_shared<MaterialIsotropic>(a))
		{
		
		}

		Medium_Constant(std::shared_ptr<Shape> b, float d, vec3 c)
			: boundary(b),neg_inv_density(-1/d),phase_function(std::make_shared<MaterialIsotropic>(c))
		{
			
		}

		virtual bool Intersect(const Ray& r,float t0,float t1,Hit& hit) const override;
		virtual bool GetBBox(float t0,float t1,AABB& output_box) const override
		{
			return boundary->GetBBox(t0, t1, output_box);
		}

	public:
		std::shared_ptr<Shape> boundary;
		std::shared_ptr<Material> phase_function;
		float neg_inv_density;
	};
}