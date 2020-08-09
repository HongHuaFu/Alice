#pragma once
#include <RayTracingCPU/Shape.hpp>
#include <RayTracingCPU/Math.hpp>
#include <RayTracingCPU/Material.hpp>
#include <RayTracingCPU/AABB.hpp>
#include <memory>

namespace Alice::RayTracingCPU
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
					hit.uv = SphereUV((hit.pos-center)/radius);
					
					return true;
				}

				temp = (-b + sqrt(discriminant)) / a;
				if (temp < tmax && temp > tmin) {
					hit.t = temp;
					hit.pos = r.At(hit.t);
					hit.normal = (hit.pos - center) * radius_inv;
					hit.material = material;
					hit.uv = SphereUV((hit.pos-center)/radius);
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

	class Sphere_Moveable : public Shape 
	{
	public:
		Sphere_Moveable() = default;
		Sphere_Moveable(vec3 cen0, vec3 cen1, float t0, float t1, float r, std::shared_ptr<Material> m)
		: center0(cen0), center1(cen1), time0(t0), time1(t1), radius(r), material(m)
		{
		
		};

		virtual bool Intersect(const Ray& r,float tmin,float tmax,Hit& hit) const override
		{
			// 与普通球体的区别主要是加了个时间变化的中心
			vec3 oc = r.GetOrigin() - center(r.GetTime());
			float a = dot(r.GetDirection(), r.GetDirection());
			float b = dot(oc, r.GetDirection());
			float c = dot(oc, oc) - radius*radius;
			float discriminant = b*b - a*c;
			if (discriminant > 0) 
			{
				float temp = (-b - sqrt(discriminant))/a;
				if (temp < tmax && temp > tmin) 
				{
					hit.t = temp;
					hit.pos = r.At(hit.t);
					// 法线这里也与时间有关
					hit.normal = (hit.pos - center(r.GetTime())) / radius;
					hit.material = material;
					return true;
				}
				temp = (-b + sqrt(discriminant))/a;
				if (temp < tmax && temp > tmin) 
				{
					hit.t = temp;
					hit.pos = r.At(hit.t);
					hit.normal = (hit.pos - center(r.GetTime())) / radius;
					hit.material = material;
					return true;
				}
			}
			return false;
		}

		// 当前时间内球的中心点
		vec3 center(float time) const
		{
			return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
		}

		virtual bool GetBBox(float t0,float t1,AABB& output_box) const override
		{
			AABB box0(
				center(t0) - vec3(radius, radius, radius),
				center(t0) + vec3(radius, radius, radius));
			AABB box1(
				center(t1) - vec3(radius, radius, radius),
				center(t1) + vec3(radius, radius, radius));
			output_box = SurroundingBox(box0, box1);
			return true;
		}

	public:
		vec3 center0, center1;
		float time0, time1;
		float radius;
		std::shared_ptr<Material> material;
	};
}