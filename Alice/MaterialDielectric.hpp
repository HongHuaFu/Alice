#pragma once

namespace Alice
{
	// 非电介质
	class MaterialDielectric : public Material
	{
	private:
		// 反射系数
		float ref_idx;

	public:
		MaterialDielectric(float ri) : ref_idx(ri) {  }

		bool Scatter(const Ray& r_in,const Hit& hit,vec3& attenuation,Ray& scattered) const override  
		{
			vec3 outward_normal;
			// 首先获取反射方向
			vec3 reflected = reflect(r_in.GetDirection(), hit.normal);

			float ni_over_nt;
			attenuation = vec3(1.0, 1.0, 1.0);

			vec3 refracted;
			float reflect_prob;
			float cosine;

			if (dot(r_in.GetDirection(), hit.normal) > 0) 
			{
				outward_normal = -hit.normal;
				ni_over_nt = ref_idx;
				cosine = dot(r_in.GetDirection(), hit.normal) / r_in.GetDirection().length();
				cosine = sqrt(1 - ref_idx * ref_idx * (1-cosine*cosine));
			}
			else 
			{
				outward_normal = hit.normal;
				ni_over_nt = 1.0 / ref_idx;
				cosine = -dot(r_in.GetDirection(), hit.normal) / r_in.GetDirection().length();
			}

			if (Refract(r_in.GetDirection(), outward_normal, ni_over_nt, refracted))
				reflect_prob = Schlick(cosine, ref_idx);
			else
				reflect_prob = 1.0;

			if (Random::GetRandom1d() < reflect_prob)
				scattered = Ray(hit.pos, reflected);
			else
				scattered = Ray(hit.pos, refracted);

			return true;
		}
	};
}