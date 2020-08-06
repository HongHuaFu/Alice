#include <Renderer.hpp>
#include <Core.hpp>
#include <Random.hpp>

namespace Alice
{
	void Renderer::Render(const Scene& scene,const std::string& path)
	{
		std::vector<unsigned char> data;
		int channel = 3;
		data.resize(sizeX * sizeY * channel,0);
		if(res == nullptr)
			res = new Image(sizeX,sizeY,3,data.data());

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
					col += RayTrace(r, scene,0);
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

		res->SaveAsTga(path);
	}


	vec3 Renderer::RayTrace(const Ray& r,const Scene& scene,int depth)
	{
		Hit hit;
		if (scene.RayTrace(r, 0.001, MaxFloat, hit)) 
		{
			Ray scattered;
			vec3 attenuation;
			if (depth < rayMaxDepth && hit.material->Scatter(r, hit, attenuation, scattered)) 
			{
				// 递归式计算光线反射
				return attenuation * RayTrace(scattered, scene, depth + 1);
			}
			else 
			{
				// 完全吸收光的情况
				return vec3(0,0,0);
			}
		}
		else // 与场景中所有物体都不相交，在这里绘制天空盒
		{
			return scene.DrawSky(r);
		}
	}
}