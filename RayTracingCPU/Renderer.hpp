#pragma once
#include <RayTracingCPU/Scene.hpp>
#include <string>
#include <RayTracingCPU/Image.hpp>

namespace Alice::RayTracingCPU
{
	class Renderer
	{
	public:
		int rayMaxDepth = 50;
		uint sizeX = 120;
		uint sizeY = 80;
		uint randomRay = 10; // 随机射线数
	protected:
		Image* res;
	public:

		// 运动模糊参数暂时放在Render函数中
		void Render(Scene& scene,const std::string& path, bool openBVH = false,float time0 = 0,float time1 = 0.0f);
	protected:
		// 单根光线在场景中做光线追踪
		// depth为光线反射次数
		vec3 RayTrace(const Ray& r,const Scene& scene,int depth);

		vec3 RayTraceBVH(const Ray& r,Scene& scene,int depth,float time0 = 0.0f,float time1 = 1.0f);
	};
}