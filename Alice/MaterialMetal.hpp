#pragma once

namespace Alice
{
	class MaterialMetal : public Material
	{
	private:
		vec3 albedo;
		float fuzz;
	public:
		MaterialMetal(const vec3& a, float f) : albedo(a) 
		{ 
			if (f < 1) 
				fuzz = f; 
			else 
				fuzz = 1; 
		}

		bool Scatter(const Ray& r_in,const Hit& hit,vec3& attenuation,Ray& scattered) const override  
		{
			// 金属表面反射
			vec3 reflected = reflect(normalize(r_in.GetDirection()), hit.normal);
			// Scatter 方向加入fuzz模糊处理
			scattered = Ray(hit.pos, reflected + fuzz * Random::GetRandom3dUint());

			attenuation = albedo;

			// 金属表面的反射光线与法线夹角不超过90度
			return dot(scattered.GetDirection(), hit.normal) > 0;
		}
	};
}