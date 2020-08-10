#pragma once
#include <RayTracingCPU/Renderer.hpp>

namespace Test::RayTracingCPU
{
	// Draw a 3d heart with phong shading model.
	inline void DrawHeart(const std::string path = "Heart.tga",uint32_t width = 256,uint32_t height = 256)
	{
		Alice::RayTracingCPU::ImageDrawHeartTest(path,width,height);
	}

	// Render Peter Shirley RayTracingInOneWeekend end scene.
	inline void RayTracingInOneWeekendScene(const std::string path = "RayTracingInOneWeekendScene.tga",uint32_t width = 1024,uint32_t height = 1024,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(13,2,3);
		vec3 lookat(0,0,0);
		float dist_to_focus = 10.0f;
		float aperture = 0.1f;

		auto scene = Scene::CreateRandomSphereScene();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path);
	}

	// Render Peter Shirley RayTracingInOneWeekend end scene with bvh accelate.
	inline void RayTracingInOneWeekendSceneBVH(const std::string path = "RayTracingInOneWeekendSceneBVH.tga",uint32_t width = 1024,uint32_t height = 1024,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(13,2,3);
		vec3 lookat(0,0,0);
		float dist_to_focus = 10.0f;
		float aperture = 0.1f;

		auto scene = Scene::CreateRandomSphereScene();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus);


		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,true);
	}

	// Render Peter Shirley RayTracingInOneWeekend end scene.
	inline void RayTracingInOneWeekendSceneMotionBlur(const std::string path = "RayTracingInOneWeekendSceneMotionBlur.tga",uint32_t width = 400,uint32_t height = 200,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(13,2,3);
		vec3 lookat(0,0,0);
		float dist_to_focus = 10.0f;
		float aperture = 0.1f;

		auto scene = Scene::CreateRandomSphereSceneMoveSphere();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus,0,1.0f);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,false,0,1.0f);
	} 

	// Render Peter Shirley RayTracingInOneWeekend end scene with checker texture.
	inline void RayTracingInOneWeekendSceneCheckerTexture(const std::string path = "RayTracingInOneWeekendSceneCheckerTexture.tga",uint32_t width = 1024,uint32_t height = 1024,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(13,2,3);
		vec3 lookat(0,0,0);
		float dist_to_focus = 10.0f;
		float aperture = 0.1f;

		auto scene = Scene::CreateRandomSphereCheckerPatternScene();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 20, float(nx)/float(ny), aperture, dist_to_focus,0,1.0f);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,false,0,1.0f);
	} 

	// An earth texture mapping sphere.
	inline void RenderEarthTexture(const std::string path = "RenderEarthTexture.tga",uint32_t width = 2048,uint32_t height = 2048,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(13,2,3);
		vec3 lookat(0,0,0);
		float dist_to_focus = 10.0f;
		float aperture = 0.0f;

		Scene scene = Scene::CreateEarthTexture();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 20.0f, float(nx)/float(ny), aperture, dist_to_focus,0,1.0f);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 100;

		r.Render(scene,path,false);
	}

	// An earth texture mapping sphere with Light rect.
	inline void RenderEarthTexturePlaneLight(const std::string path = "RenderEarthTexturePlaneLight.tga",uint32_t width = 1024,uint32_t height = 1024,uint32_t sampleTimes = 100)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(26,3,6);
		vec3 lookat(0,2,0);
		float dist_to_focus = 10.0f;
		float aperture = 0.0f;

		Scene scene = Scene::CreateEarthTextureAndRectLight();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 20.0f, float(nx)/float(ny), aperture, dist_to_focus,0,1.0f);
		scene.background_color = vec3(0);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 200;

		r.Render(scene,path,true,0,0,true);
	}


	// An empty cornell box scene.
 	inline void EmptyCornellBox(const std::string path = "EmptyCornellBox.tga",uint32_t width = 256,uint32_t height = 256,uint32_t sampleTimes = 200)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(278, 278, -800);
		vec3 lookat(278, 278, 0);
		float dist_to_focus = 10.0f;
		float aperture = 0.0f;

		Scene scene = Scene::CreateCornellBoxEmpty();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 40.0f, float(nx)/float(ny), aperture, dist_to_focus,0,0.0f);
		scene.background_color = vec3(0);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,false,0,0,true);
	}

	// An cornell box scene.
	inline void CornellBox(const std::string path = "CornellBox.tga",uint32_t width = 256,uint32_t height = 256,uint32_t sampleTimes = 200)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(278, 278, -800);
		vec3 lookat(278, 278, 0);
		float dist_to_focus = 10.0f;
		float aperture = 0.0f;

		Scene scene = Scene::CreateCornellBox();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 40.0f, float(nx)/float(ny), aperture, dist_to_focus,0,0.0f);
		scene.background_color = vec3(0);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,true,0,0,true);
	}

	// An cornell box smoke scene.
	inline void CornellSmokeBox(const std::string path = "CornellSmokeBox.tga",uint32_t width = 256,uint32_t height = 256,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(278, 278, -800);
		vec3 lookat(278, 278, 0);
		float dist_to_focus = 10.0f;
		float aperture = 0.0f;

		Scene scene = Scene::CreateCornellSmokeBox();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 40.0f, float(nx)/float(ny), aperture, dist_to_focus,0,0.0f);
		scene.background_color = vec3(0);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,true,0,0,true);
	}


	inline void RayTracingNextWeekFinalScene(const std::string path = "RayTracingNextWeekFinalScene.tga",uint32_t width = 256,uint32_t height = 256,uint32_t sampleTimes = 10)
	{
		using namespace Alice::RayTracingCPU;
		int nx = width;
		int ny = height;
		int ns = sampleTimes;

		vec3 lookfrom(478, 278, -600);
		vec3 lookat(278, 278, 00);
		float dist_to_focus = 10.0f;
		float aperture = 0.0f;

		Scene scene = Scene::NextWeekFinalScene();
		scene.camera = std::make_shared<Camera>(lookfrom, lookat, vec3(0,1,0), 40.0f, float(nx)/float(ny), aperture, dist_to_focus,0,0.0f);
		scene.background_color = vec3(0);

		Renderer r;
		r.sizeX = nx;
		r.sizeY = ny;
		r.randomRay = ns;
		r.rayMaxDepth = 50;

		r.Render(scene,path,true,0,0,true);
	}
}

