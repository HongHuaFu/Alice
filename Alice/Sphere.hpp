#pragma once
#include <Shape.hpp>
#include <Math.hpp>
#include <Material.hpp>
#include <AABB.hpp>
#include <memory>

namespace Alice
{
	class Sphere : public Shape
	{
	public:
		Sphere() = default;
		Sphere(vec3 cen, float r, std::shared_ptr<Material> m) : center(cen), radius(r), material(m),radius2(r * r),radius_inv(1.0f / r) { };

		float GetRadius() const { return radius; }
		void SetRadius(float r) { radius = r; radius2 = r * r; radius_inv = 1.0f / r; }

		virtual bool GetBBox(float t0,float t1,AABB& output_box) const override
		{
			output_box = AABB(center - vec3(radius, radius, radius), center + vec3(radius, radius, radius));
			return true;
		}

		virtual bool Intersect(const Ray& r,float tmin,float tmax,Hit& hit) const override
		{
			vec3 oc = r.GetOrigin() - center;
			float a = dot(r.GetDirection(), r.GetDirection());
			float b = dot(oc, r.GetDirection());
			float c = dot(oc, oc) - radius2;
			float discriminant = b*b - a*c;

			if (discriminant > 0) 
			{
				float temp = (-b - sqrt(discriminant)) / a;
				if (temp < tmax && temp > tmin) {
					hit.t = temp;
					hit.pos = r.At(hit.t);
					hit.normal = (hit.pos - center) * radius_inv;
					hit.material = material;
					return true;
				}

				temp = (-b + sqrt(discriminant)) / a;
				if (temp < tmax && temp > tmin) {
					hit.t = temp;
					hit.pos = r.At(hit.t);
					hit.normal = (hit.pos - center) * radius_inv;
					hit.material = material;
					return true;
				}
			}
			return false;
		}

	public:
		std::shared_ptr<Material> material;
		vec3 center;

	protected:
		float radius,radius2,radius_inv;
	};
}