#include <Renderer.hpp>

using namespace Alice;

int main()
{
	int nx = 1024;
	int ny = 1024;
	int ns = 10;

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
	
	r.Render(scene,"hello.tga");

	return 0;
}

