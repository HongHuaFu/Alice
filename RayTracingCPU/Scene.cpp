#include <RayTracingCPU/Scene.hpp>
#include <RayTracingCPU/BVH.hpp>

namespace Alice::RayTracingCPU
{
	bool Scene::GetBBox(float t0,float t1,AABB& out_box) const
	{
		if (shapes.empty()) return false;

		AABB temp_box;
		bool first_box = true;

		for (const auto& shape : shapes) 
		{
			// 第一次启用时构建
			if (!shape->GetBBox(t0, t1, temp_box)) 
				return false;

			out_box = first_box ? temp_box : SurroundingBox(out_box, temp_box);
			first_box = false;
		}

		return true;
	}

	bool Scene::RayTrace(const Ray& r,float tmin,float tmax,Hit& hit,float time0,float time1) const
	{
		Hit temp_rec;
		bool hitAnything = false;
		float closest_so_far = tmax;

		// 遍历所有物体求交
		for (int i = 0; i < shapes.size(); i++) {
			if (shapes[i]->Intersect(r, tmin, closest_so_far, temp_rec)) {
				// 选择最近的相交物体
				hitAnything = true;
				closest_so_far = temp_rec.t;
				hit = temp_rec;
			}
		}
		return hitAnything;
	}

	bool Scene::RayTraceBVH(const Ray& r,float tmin,float tmax,Hit& hit,float time0,float time1)
	{
		Hit temp_rec;
		bool hitAnything = false;
		float closest_so_far = tmax;

		if(!start_raytracing)
		{
			// 第一次追踪 先构建BBox和BVH
			GetBBox(time0,time1,scene_aabb);
			scene_bvh = std::make_shared<BVH_Node>(*this,time0,time1);
			start_raytracing = true;
		}

		if(!scene_aabb.Intersect(r,tmin,tmax))
			return false;

		hitAnything = scene_bvh->Intersect(r,tmin,tmax,hit);
		return hitAnything;
	}
}