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
		uint randomRay = 10; // ���������
	protected:
		Image* res;
	public:

		// �˶�ģ��������ʱ����Render������
		void Render(Scene& scene,const std::string& path, bool openBVH = false,float time0 = 0,float time1 = 0.0f);
	protected:
		// ���������ڳ�����������׷��
		// depthΪ���߷������
		vec3 RayTrace(const Ray& r,const Scene& scene,int depth);

		vec3 RayTraceBVH(const Ray& r,Scene& scene,int depth,float time0 = 0.0f,float time1 = 1.0f);
	};
}