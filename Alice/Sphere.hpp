#pragma once
#include <Shape.hpp>
#include <Math.hpp>
#include <Material.hpp>

namespace Alice
{
	class Sphere final : public Shape
	{
	private:
		glm::vec3 center;
		// Store square of radius to accelerate.
		float radius, radius2;
		Material* material;

	public:
		Sphere(const glm::vec3& c, const float& r,Material* m) : center(c),radius(r),radius2(r * r),material(m){ }

		Material* GetMaterial() const override
		{
			return material;
		}



		// Sphere intersect judge.
		bool Intersect(const Ray& ray) const override
		{
			// Analytic solution
			glm::vec3 L = ray.origin - center;
			float a = glm::dot(ray.direction, ray.direction);
			float b = 2 * glm::dot(ray.direction, L);
			float c = glm::dot(L, L) - radius2;
			float t0, t1;
			if (!SolveQuadratic(a,b,c,t0,t1))
				return false;
			if (t0 < 0)
				t0 = t1;
			if (t0 < 0)
				return false;
			return true;
		}

		// TODO: Sphere uv need to fix.
		bool Intersect(const Ray& ray,glm::vec2& uv) const override
		{
			glm::vec3 L = ray.origin - center;
			float a = glm::dot(ray.direction, ray.direction);
			float b = 2 * glm::dot(ray.direction, L);
			float c = glm::dot(L, L) - radius2;
			float t0, t1;
			if (!SolveQuadratic(a, b, c, t0, t1)) 
				return false;
			if (t0 < 0) 
				t0 = t1;
			if (t0 < 0) 
				return false;
			return true;
		}

		// Sphere intersect judge.
		// Then return intersect distance - t value.
		bool Intersect(const Ray& ray, float& tnear, uint32_t& index,glm::vec2&) const override
		{
			// analytic solution
			glm::vec3 L = ray.origin - center;
			float a = glm::dot(ray.direction, ray.direction);
			float b = 2 * glm::dot(ray.direction, L);
			float c = glm::dot(L, L) - radius2;
			float t0, t1;
			if (!SolveQuadratic(a, b, c, t0, t1)) 
				return false;
			if (t0 < 0) 
				t0 = t1;
			if (t0 < 0) 
				return false;
			tnear = t0;
			return true;
		}

		void GetSurfaceProperties(const glm::vec3& P, const glm::vec3& I, const uint32_t &index, const glm::vec2& uv, glm::vec3& N, glm::vec2& st) const override
		{
			N = normalize(P - center); 
		}

		glm::vec3 EvalDiffuseColor(const glm::vec2& st) const override
		{
			return material->GetColor();
		}
	};
}