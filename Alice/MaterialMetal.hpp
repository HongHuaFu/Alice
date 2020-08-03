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
			// �������淴��
			vec3 reflected = reflect(normalize(r_in.GetDirection()), hit.normal);
			// Scatter �������fuzzģ������
			scattered = Ray(hit.pos, reflected + fuzz * Random::GetRandom3dUint());

			attenuation = albedo;

			// ��������ķ�������뷨�߼нǲ�����90��
			return dot(scattered.GetDirection(), hit.normal) > 0;
		}
	};
}