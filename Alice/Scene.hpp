#pragma once
#include <vector>
#include <memory>
#include <Math.hpp>
#include <Shape.hpp>
#include <Camera.hpp>
#include <Sphere.hpp>
#include <Material.hpp>
#include <MaterialDielectric.hpp>
#include <MaterialLambert.hpp>
#include <MaterialMetal.hpp>

namespace Alice
{
	class Scene
	{
	public:
		std::vector<std::shared_ptr<Shape>> shapes;
		std::shared_ptr<Camera> camera;
	public:
		Scene() = default;
		void AddShapePtrRef(std::shared_ptr<Shape> shape) { shapes.push_back(shape); }

		// 获取场景的包围盒
		bool GetBBox(float t0,float t1,AABB& out_box) const
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

		bool RayTrace(const Ray& r,float tmin,float tmax,Hit& hit) const
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

		// 在与所有几何体都不相交时，在这里绘制天空
		vec3 DrawSky(const Ray& r) const
		{
			vec3 unit_direction = normalize(r.GetDirection());
			float t = 0.5f * (unit_direction.y + 1.0f);
			return (1.0f - t) * vec3(1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
		}

		static Scene CreateRandomSphereScene()
		{
			Scene res;
			int n = 500;

			std::shared_ptr<Shape> s0 =  std::make_shared<Sphere>(vec3(0,-1000.0f,0), 1000.0f,std::make_shared<MaterialLambert>(vec3(0.5, 0.5, 0.5)));
			res.shapes.push_back(s0);
			int i = 1;
			for (int a = -11; a < 11; a++) 
			{
				for (int b = -11; b < 11; b++) 
				{
					float choose_mat = Random::GetRandom1d();
					vec3 center(a+0.9*Random::GetRandom1d(),0.2f,b+0.9f*Random::GetRandom1d());
					if ((center-vec3(4.0f,0.2f,0)).length() > 0.9f) 
					{
						if (choose_mat < 0.8f) 
						{  
							// diffuse
							res.shapes.push_back(std::make_shared<Sphere>(
								center, 0.2,
								std::make_shared<MaterialLambert>(vec3(Random::GetRandom1d()* Random::GetRandom1d(),Random::GetRandom1d()*Random::GetRandom1d(),Random::GetRandom1d()*Random::GetRandom1d()))));
						}
						else if (choose_mat < 0.95) 
						{ 
							// metal
							res.shapes.push_back(std::make_shared<Sphere>(
								center, 0.2,
								std::make_shared<MaterialMetal>(vec3(0.5f*(1 + Random::GetRandom1d()),
									0.5f*(1 + Random::GetRandom1d()),
									0.5f*(1 + Random::GetRandom1d())),
									0.5f*Random::GetRandom1d())));
						}
						else 
						{  
							// glass
							res.shapes.push_back(std::make_shared<Sphere>(center, 0.2, std::make_shared<MaterialDielectric>(1.5f)));
						}
					}
				}
			}

			res.shapes.push_back(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0, std::make_shared<MaterialDielectric>(1.5)));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(-4, 1, 0), 1.0, std::make_shared<MaterialLambert>(vec3(0.4, 0.2, 0.1))));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(4, 1, 0), 1.0, std::make_shared<MaterialMetal>(vec3(0.7, 0.6, 0.5), 0.0)));

			return res;
		}
	};
}

