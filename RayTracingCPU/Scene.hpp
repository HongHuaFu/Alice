#pragma once
#include <vector>
#include <memory>
#include <RayTracingCPU/Math.hpp>
#include <RayTracingCPU/Shape.hpp>
#include <RayTracingCPU/Camera.hpp>
#include <RayTracingCPU/Sphere.hpp>
#include <RayTracingCPU/Material.hpp>
#include <RayTracingCPU/MaterialDielectric.hpp>
#include <RayTracingCPU/MaterialLambert.hpp>
#include <RayTracingCPU/MaterialMetal.hpp>
#include <RayTracingCPU/AABB.hpp>
#include <RayTracingCPU/Texture.hpp>

namespace Alice::RayTracingCPU
{
	class BVH_Node;
	class Scene
	{
	public:
		std::vector<std::shared_ptr<Shape>> shapes;
		std::shared_ptr<Camera> camera;
		AABB scene_aabb;
		std::shared_ptr<BVH_Node> scene_bvh;
		bool start_raytracing = false;
		vec3 background_color = vec3(0);
	public:
		Scene() = default;
		void AddShapePtrRef(std::shared_ptr<Shape> shape) { shapes.push_back(shape); }

		// 获取场景的包围盒
		bool GetBBox(float t0,float t1,AABB& out_box) const;
		

		// 光线追踪 无BVH加速
		bool RayTrace(const Ray& r,float tmin,float tmax,Hit& hit,float time0 = 0.0f,float time1 = 0.0f) const;
		

		// 光线追踪 BVH加速
		bool RayTraceBVH(const Ray& r,float tmin,float tmax,Hit& hit,float time0 = 0.0f,float time1 = 0.0f);
		

		// 在与所有几何体都不相交时，在这里绘制天空
		vec3 DrawSky(const Ray& r,bool return_background = false) const
		{
			if(return_background)
				return background_color;
			vec3 unit_direction = normalize(r.GetDirection());
			float t = 0.5f * (unit_direction.y + 1.0f);
			return (1.0f - t) * vec3(1.0f) + t * vec3(0.5f, 0.7f, 1.0f);
		}

		static Scene CreateRandomSphereScene()
		{
			Scene res;

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

			res.shapes.push_back(std::make_shared<Sphere>(vec3(0, 1.0f, 0), 1.0f, std::make_shared<MaterialDielectric>(1.5f)));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, 0), 1.0f, std::make_shared<MaterialLambert>(vec3(0.4f, 0.2f, 0.1f))));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(4.0f, 1.0f, 0), 1.0f, std::make_shared<MaterialMetal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

			return res;
		}

		static Scene CreateRandomSphereSceneMoveSphere()
		{
			Scene res;

			std::shared_ptr<Shape> s0 =  std::make_shared<Sphere>(vec3(0,-1000.0f,0), 1000.0f,std::make_shared<MaterialLambert>(vec3(0.5, 0.5, 0.5)));
			res.shapes.push_back(s0);
			int i = 1;
			for (int a = -11; a < 11; a++) 
			{
				for (int b = -11; b < 11; b++) 
				{
					auto mat_motion_blur_lambert = std::make_shared<MaterialLambert>(vec3(Random::GetRandom1d()* Random::GetRandom1d(),Random::GetRandom1d()*Random::GetRandom1d(),Random::GetRandom1d()*Random::GetRandom1d()));

					float choose_mat = Random::GetRandom1d();
					vec3 center(a+0.9*Random::GetRandom1d(),0.2f,b+0.9f*Random::GetRandom1d());
					if ((center-vec3(4.0f,0.2f,0)).length() > 0.9f) 
					{
						if (choose_mat < 0.8f) 
						{  
							// diffuse with motion blur
							auto center2 = center + vec3(0, Random::GetRandom1d(0,.5f), 0);
							res.shapes.push_back(std::make_shared<Sphere_Moveable>(
								center, center2, 0.0f, 1.0f, 0.2f, mat_motion_blur_lambert));
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

			res.shapes.push_back(std::make_shared<Sphere>(vec3(0, 1, 0), 1.0f, std::make_shared<MaterialDielectric>(1.5f)));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, 0), 1.0f, std::make_shared<MaterialLambert>(vec3(0.4f, 0.2f, 0.1f))));

			auto center2 = vec3(4.0f, 1.0f, 0) + vec3(0, Random::GetRandom1d(0,.5f), 0);
			res.shapes.push_back(std::make_shared<Sphere_Moveable>(vec3(4.0f, 1.0f, 0),center2,0,1.0f, 1.0f, std::make_shared<MaterialMetal>(vec3(0.7f, 0.6f, 0.5f), 0.0)));

			return res;
		}

		static Scene CreateRandomSphereCheckerPatternScene()
		{
			Scene res;
			auto checker = std::make_shared<TextureCheckerTexture>(vec3(0.2f, 0.3f, 0.1f), vec3(0.9f, 0.9f, 0.9f));
			std::shared_ptr<Shape> s0 =  std::make_shared<Sphere>(vec3(0,-1000.0f,0), 1000.0f,std::make_shared<MaterialLambert>(checker));
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

			res.shapes.push_back(std::make_shared<Sphere>(vec3(0, 1.0f, 0), 1.0f, std::make_shared<MaterialDielectric>(1.5f)));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(-4.0f, 1.0f, 0), 1.0f, std::make_shared<MaterialLambert>(vec3(0.4f, 0.2f, 0.1f))));
			res.shapes.push_back(std::make_shared<Sphere>(vec3(4.0f, 1.0f, 0), 1.0f, std::make_shared<MaterialMetal>(vec3(0.7f, 0.6f, 0.5f), 0.0f)));

			return res;
		}

		static Scene CreateEarthTexture(const char* path = "./Asset/Textures/2k_earth_daymap.jpg")
		{
			Scene res;
			auto earth_texture = std::make_shared<TextureImage>(path);
			auto earth_surface = std::make_shared<MaterialLambert>(earth_texture);
			auto globe = std::make_shared<Sphere>(vec3(0,0,0), 2, earth_surface);
			res.shapes.push_back(globe);
			return res;
		}
	};
}

