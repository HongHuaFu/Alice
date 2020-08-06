#pragma once
#include <Scene.hpp>
#include <string>
#include <Image.hpp>

namespace Alice
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
		void Render(const Scene& scene,const std::string& path);
	protected:
		// 单根光线在场景中做光线追踪
		// depth为光线反射次数
		vec3 RayTrace(const Ray& r,const Scene& scene,int depth);
	};
}