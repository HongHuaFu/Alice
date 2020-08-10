#include <RayTracingCPU/Scene.hpp>
#include <RayTracingCPU/BVH.hpp>
#include <RayTracingCPU/Box.hpp>
#include <RayTracingCPU/Translate.hpp>
#include <RayTracingCPU/Medium.hpp>

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

	Scene Scene::CreateCornellBox()
	{
		Scene res;
		auto red   = std::make_shared<MaterialLambert>(vec3(.65, .05, .05));
		auto white = std::make_shared<MaterialLambert>(vec3(.73, .73, .73));
		auto green = std::make_shared<MaterialLambert>(vec3(.12, .45, .15));
		auto light = std::make_shared<MaterialDiffuseLight>(vec3(15, 15, 15));

		res.shapes.push_back(std::make_shared<AABB_Rect_YZ>(0, 555, 0, 555, 555, green));
		res.shapes.push_back(std::make_shared<AABB_Rect_YZ>(0, 555, 0, 555, 0, red));
		res.shapes.push_back(std::make_shared<AABB_Rect_XZ>(213, 343, 227, 332, 554, light));
		res.shapes.push_back(std::make_shared<AABB_Rect_XZ>(0, 555, 0, 555, 0, white));
		res.shapes.push_back(std::make_shared<AABB_Rect_XZ>(0, 555, 0, 555, 555, white));
		res.shapes.push_back(std::make_shared<AABB_Rect_XY>(0, 555, 0, 555, 555, white));

		std::shared_ptr<Shape> box1 = std::make_shared<Box>(vec3(0, 0, 0), vec3(165, 330, 165), white);
		box1 = std::make_shared<Rotate_Y>(box1, 15);
		box1 = std::make_shared<Translate>(box1, vec3(265,0,295));
		res.shapes.push_back(box1);

		std::shared_ptr<Shape> box2 = std::make_shared<Box>(vec3(0,0,0), vec3(165,165,165), white);
		box2 = std::make_shared<Rotate_Y>(box2, -18);
		box2 = std::make_shared<Translate>(box2, vec3(130,0,65));
		res.shapes.push_back(box2);
		return res;
	}

	Scene Scene::CreateCornellSmokeBox()
	{
		Scene res;
		auto red   = std::make_shared<MaterialLambert>(vec3(.65, .05, .05));
		auto white = std::make_shared<MaterialLambert>(vec3(.73, .73, .73));
		auto green = std::make_shared<MaterialLambert>(vec3(.12, .45, .15));
		auto light = std::make_shared<MaterialDiffuseLight>(vec3(15, 15, 15));

		res.shapes.push_back(std::make_shared<AABB_Rect_YZ>(0, 555, 0, 555, 555, green));
		res.shapes.push_back(std::make_shared<AABB_Rect_YZ>(0, 555, 0, 555, 0, red));
		res.shapes.push_back(std::make_shared<AABB_Rect_XZ>(213, 343, 227, 332, 554, light));
		res.shapes.push_back(std::make_shared<AABB_Rect_XZ>(0, 555, 0, 555, 0, white));
		res.shapes.push_back(std::make_shared<AABB_Rect_XZ>(0, 555, 0, 555, 555, white));
		res.shapes.push_back(std::make_shared<AABB_Rect_XY>(0, 555, 0, 555, 555, white));

		std::shared_ptr<Shape> box1 = std::make_shared<Box>(vec3(0, 0, 0), vec3(165, 330, 165), white);
		box1 = std::make_shared<Rotate_Y>(box1, 15);
		box1 = std::make_shared<Translate>(box1, vec3(265,0,295));

		std::shared_ptr<Shape> box2 = std::make_shared<Box>(vec3(0,0,0), vec3(165,165,165), white);
		box2 = std::make_shared<Rotate_Y>(box2, -18);
		box2 = std::make_shared<Translate>(box2, vec3(130,0,65));

		res.shapes.push_back(std::make_shared<Medium_Constant>(box1, 0.01, vec3(0,0,0)));
		res.shapes.push_back(std::make_shared<Medium_Constant>(box2, 0.01, vec3(1,1,1)));

		return res;
	}

	Scene Scene::NextWeekFinalScene(const char* imagepath) 
	{
		Scene boxes1;
		auto ground = std::make_shared<MaterialLambert>(vec3(0.48, 0.83, 0.53));

		const int boxes_per_side = 20;
		for (int i = 0; i < boxes_per_side; i++) 
		{
			for (int j = 0; j < boxes_per_side; j++) 
			{
				auto w = 100.0;
				auto x0 = -1000.0 + i*w;
				auto z0 = -1000.0 + j*w;
				auto y0 = 0.0;
				auto x1 = x0 + w;
				auto y1 = Random::GetRandom1d(1,101);
				auto z1 = z0 + w;

				boxes1.AddShapePtrRef(std::make_shared<Box>(vec3(x0,y0,z0), vec3(x1,y1,z1), ground));
			}
		}

		Scene objects;

		objects.AddShapePtrRef(std::make_shared<BVH_Node>(boxes1, 0, 1));

		auto light = std::make_shared<MaterialDiffuseLight>(vec3(7, 7, 7));
		objects.AddShapePtrRef(std::make_shared<AABB_Rect_XZ>(123, 423, 147, 412, 554, light));

		auto center1 = vec3(400, 400, 200);
		auto center2 = center1 + vec3(30,0,0);
		auto moving_sphere_material = std::make_shared<MaterialLambert>(vec3(0.7, 0.3, 0.1));

		objects.AddShapePtrRef(std::make_shared<Sphere_Moveable>(center1, center2, 0, 1, 50, moving_sphere_material));

		objects.AddShapePtrRef(std::make_shared<Sphere>(vec3(260, 150, 45), 50, std::make_shared<MaterialDielectric>(1.5)));
		objects.AddShapePtrRef(std::make_shared<Sphere>(
			vec3(0, 150, 145), 50,std::make_shared<MaterialMetal>(vec3(0.8, 0.8, 0.9), 10.0)
			));

		auto boundary = std::make_shared<Sphere>(vec3(360,150,145), 70, std::make_shared<MaterialDielectric>(1.5));
		objects.AddShapePtrRef(boundary);
		objects.AddShapePtrRef(std::make_shared<Medium_Constant>(boundary, 0.2, vec3(0.2, 0.4, 0.9)));
		boundary = std::make_shared<Sphere>(vec3(0, 0, 0), 5000, std::make_shared<MaterialDielectric>(1.5));
		
		objects.AddShapePtrRef(std::make_shared<Medium_Constant>(boundary, .0001, vec3(1,1,1)));

		auto emat = std::make_shared<MaterialLambert>(std::make_shared<TextureImage>(imagepath));
		objects.AddShapePtrRef(std::make_shared<Sphere>(vec3(400,200,400), 100, emat));

		Scene boxes2;
		auto white = std::make_shared<MaterialLambert>(vec3(.73, .73, .73));
		int ns = 1000;
		for (int j = 0; j < ns; j++) {
			boxes2.AddShapePtrRef(std::make_shared<Sphere>(Random::GetRandom3d(0,165), 10, white));
		}

		objects.AddShapePtrRef(std::make_shared<Translate>(
			std::make_shared<Rotate_Y>(
				std::make_shared<BVH_Node>(boxes2, 0.0, 1.0), 15),
			vec3(-100,270,395)
			)
		);

		return objects;
	}
}