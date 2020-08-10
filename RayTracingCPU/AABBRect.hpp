#pragma once
#include <RayTracingCPU/Shape.hpp>
#include <RayTracingCPU/Material.hpp>
#include <RayTracingCPU/AABB.hpp>

namespace Alice::RayTracingCPU
{
	// xy平面的轴对齐四边形
	class AABB_Rect_XY : public Shape
	{
	public:
		AABB_Rect_XY() {}

		AABB_Rect_XY(float _x0, float _x1, float _y0, float _y1, float _k, std::shared_ptr<Material> mat)
			: x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), material(mat) 
		{
		
		}

		virtual bool Intersect(const Ray& r,float t0,float t1,Hit& hit) const override
		{
			auto t = (k-r.GetOrigin().z) / r.GetDirection().z;
			if (t < t0 || t > t1)
				return false;
			auto x = r.GetOrigin().x + t * r.GetDirection().x;
			auto y = r.GetOrigin().y + t * r.GetDirection().y;

			if (x < x0 || x > x1 || y < y0 || y > y1)
				return false;

			hit.uv.x = (x-x0)/(x1-x0);
			hit.uv.y = (y-y0)/(y1-y0);

			hit.t = t;
			auto outward_normal = vec3(0, 0, 1);
			if(dot(outward_normal,r.GetDirection()) > 0)
				outward_normal = vec3(0, 0, -1);

			hit.normal = outward_normal;
			hit.material = material;
			hit.pos = r.At(t);
			return true;
		}

		virtual bool GetBBox(float t0, float t1, AABB& output_box) const override 
		{
			// The bounding box must have non-zero width in each dimension, so pad the Z
			// dimension a small amount.
			output_box = AABB(vec3(x0,y0, k-0.0001f), vec3(x1, y1, k+0.0001f));
			return true;
		}

	public:
		std::shared_ptr<Material> material;
		float x0, x1, y0, y1, k;
	};


	class AABB_Rect_XZ : public Shape
	{
	public:
		AABB_Rect_XZ() {}

		AABB_Rect_XZ(float _x0, float _x1, float _z0, float _z1, float _k,std::shared_ptr<Material> material)
		: x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), material(material)
		{
		
		}

		virtual bool Intersect(const Ray& r,float t0,float t1,Hit& hit) const override
		{
			auto t = (k-r.GetOrigin().y) / r.GetDirection().y;
			if (t < t0 || t > t1)
				return false;
			auto x = r.GetOrigin().x + t*r.GetDirection().x;
			auto z = r.GetOrigin().z + t*r.GetDirection().z;
			if (x < x0 || x > x1 || z < z0 || z > z1)
				return false;
			hit.uv.x = (x-x0)/(x1-x0);
			hit.uv.y = (z-z0)/(z1-z0);
			hit.t = t;
			auto outward_normal = vec3(0, 1.0f, 0);
			if(dot(outward_normal,r.GetDirection()) > 0)
				outward_normal = vec3(0, -1, 0);
			hit.normal = outward_normal;
			hit.material = material;
			hit.pos = r.At(t);
			return true;
		}

		virtual bool GetBBox(float t0, float t1, AABB& output_box) const override 
		{
			output_box = AABB(vec3(x0,k-0.0001f, z0), vec3(x1, k+0.0001f, z1));
			return true;
		}

	public:
		std::shared_ptr<Material> material;
		float x0, x1, z0, z1, k;
	};

	class AABB_Rect_YZ : public Shape
	{
	public:
		AABB_Rect_YZ() {}

		AABB_Rect_YZ(float _y0, float _y1, float _z0, float _z1, float _k,std::shared_ptr<Material> material)
			: y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), material(material)
		{

		}

		virtual bool Intersect(const Ray& r,float t0,float t1,Hit& hit) const override
		{
			auto t = (k-r.GetOrigin().x) / r.GetDirection().x;
			if (t < t0 || t > t1)
				return false;
			auto y = r.GetOrigin().y + t*r.GetDirection().y;
			auto z = r.GetOrigin().z + t*r.GetDirection().z;
			if (y < y0 || y > y1 || z < z0 || z > z1)
				return false;
			hit.uv.x = (y-y0)/(y1-y0);
			hit.uv.y = (z-z0)/(z1-z0);
			hit.t = t;
			auto outward_normal = vec3(1, 0, 0);
			if(dot(outward_normal,r.GetDirection()) > 0)
				outward_normal = vec3(-1, 0, 0);

			hit.normal = outward_normal;
			hit.material = material;
			hit.pos = r.At(t);
			return true;
		}

		virtual bool GetBBox(float t0, float t1, AABB& output_box) const override 
		{
			output_box = AABB(vec3(k-0.0001f,y0, z0), vec3( k+0.0001f,y1, z1));
			return true;
		}

	public:
		std::shared_ptr<Material> material;
		float y0, y1, z0, z1, k;
	};
}