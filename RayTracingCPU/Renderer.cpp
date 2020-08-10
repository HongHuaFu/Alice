#include <RayTracingCPU/Renderer.hpp>
#include <RayTracingCPU/Core.hpp>
#include <RayTracingCPU/Random.hpp>
#include <RayTracingCPU/Timer.hpp>

namespace Alice::RayTracingCPU
{
	void Renderer::Render(Scene& scene,const std::string& path,bool openBVH,float time0,float time1,bool background_color)
	{
		std::vector<unsigned char> data;
		int channel = 3;
		data.resize(sizeX * sizeY * channel,0);
		if(res == nullptr)
			res = new Image(sizeX,sizeY,3,data.data());

		std::cout << "Alice is rendering picture on "<< path << " for you." << std::endl;
		Timer timer;
		timer.Start();

		for (int j = sizeY-1; j >= 0; j--) 
		{
			for (int i = 0; i < sizeX; i++) 
			{
				vec3 col(0);

				for (int s=0; s < randomRay; s++) 
				{
					float u = float(i + Random::GetRandom1d()) / float(sizeX);
					float v = float(j + Random::GetRandom1d()) / float(sizeY);
					Ray r = scene.camera->CastRay(u, v);

					if(openBVH)
						col += RayTraceBVH(r, scene,0,time0,time1,background_color);
					else
						col += RayTrace(r, scene,0,background_color);
				}
				col /= float(randomRay);

				col = vec3( sqrt(col[0]), sqrt(col[1]), sqrt(col[2]) );
				
				unsigned char ir = unsigned char(255.99f*col[0]);
				unsigned char ig = unsigned char(255.99f*col[1]);
				unsigned char ib = unsigned char(255.99f*col[2]);
				res->SetPixel(i,j,ir,ig,ib);
			}

			PrintRenderProgress(1 - float(j) / float(sizeY));
		}

		timer.Stop();
		std::cout<< std::endl;
		std::cout << "Alice has finished work and the result put on "<< path << "." << std::endl;
		std::cout << "Totally used time: "<< timer.Elapsed(TimeUnit::SS) << "s." << std::endl;
		std::cout << std::flush;

		res->SaveAsTga(path);
	}


	vec3 Renderer::RayTrace(const Ray& r,const Scene& scene,int depth,bool background)
	{
		Hit hit;

		if(depth >= rayMaxDepth) // 完全吸收光的情况
			return vec3(0,0,0);

		if(!scene.RayTrace(r,0.001f,MaxFloat,hit)) // 与场景中所有物体都不相交，在这里绘制天空
		{
			if(background) return scene.background_color;
			return scene.DrawSky(r);
		}

		Ray scattered;
		vec3 attenuation;
		vec3 emitted = hit.material->Emitted(hit.uv.x,hit.uv.y,hit.pos);
		if (hit.material->Scatter(r, hit, attenuation, scattered)) // 递归式计算光线反射
			return emitted + attenuation * RayTrace(scattered, scene, depth + 1,background);

		return emitted; // 光源渲染
	}

	// BVH加速的光线追踪
	vec3 Renderer::RayTraceBVH(const Ray& r,Scene& scene,int depth,float time0,float time1,bool background)
	{
		Hit hit;

		if(depth >= rayMaxDepth) // 完全吸收光的情况
			return vec3(0,0,0);

		if(!scene.RayTraceBVH(r,0.001f,MaxFloat,hit,0,0)) 
		{
			// 与场景中所有物体都不相交，在这里绘制天空
			if(background) return scene.background_color;
			return scene.DrawSky(r);
		}

		Ray scattered;
		vec3 attenuation;
		vec3 emitted = hit.material->Emitted(hit.uv.x,hit.uv.y,hit.pos);
		if (hit.material->Scatter(r, hit, attenuation, scattered)) // 递归式计算光线反射
			return emitted + attenuation * RayTraceBVH(scattered, scene, depth + 1,0,0,background);

		return emitted; // 光源渲染
	}

}