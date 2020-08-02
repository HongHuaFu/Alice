#include <Renderer.hpp>
#include <Scene.hpp>
#include <Sphere.hpp>
#include <Triangle.hpp>
#include <Material.hpp>

using namespace Alice;

int main()
{
	Scene scene(512, 512);
	auto diffuseMat = new Material();
	auto glassMat = new Material();

	diffuseMat->type = MaterialType::DIFFUSE_AND_GLOSSY;
	diffuseMat->color =  glm::vec3(0.6, 0.7, 0.8);
	glassMat->type = MaterialType::REFLECTION_AND_REFRACTION;
	glassMat->ior = 1.5f;
	auto sph1 = new Sphere(glm::vec3(-1, 0, -12), 2,diffuseMat);
	auto sph2 = new Sphere(glm::vec3(0.5, -0.5, -8), 1.5,glassMat);

	auto triangleMat = new Material();
	triangleMat->type = MaterialType::DIFFUSE_AND_GLOSSY;
	auto image = ImageLoad("sora.png");
	triangleMat->texture = &image;
	glm::vec3 verts[4] = {{-5,-3,-6}, {5,-3,-6}, {5,-3,-16}, {-5,-3,-16}};
	uint32_t vertIndex[6] = {0, 1, 3, 1, 2, 3};
	glm::vec2 st[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};

	Shape* PlaneMesh = new MeshTriangle(verts, vertIndex, 2, st,triangleMat);

	auto Triangle1 = new Triangle(verts[0],verts[1],verts[3],triangleMat);
	Triangle1->t0 = st[0];
	Triangle1->t1 = st[1];
	Triangle1->t2 = st[3];

	auto Triangle2 = new Triangle(verts[1],verts[2],verts[3],triangleMat);
	Triangle1->t0 = st[1];
	Triangle1->t1 = st[2];
	Triangle1->t2 = st[3];

	scene.AddShapeReference(sph1);
	scene.AddShapeReference(sph2);
	// scene.AddShapeReference(Triangle1);
	// scene.AddShapeReference(Triangle2);
	scene.AddShapeReference(PlaneMesh);
	scene.AddLightReference(new Light(glm::vec3(-20, 70, 20), glm::vec3(0.5)));
	scene.AddLightReference(new Light(glm::vec3(30, 50, -12), glm::vec3(0.5)));    

	Renderer r;

	std::cout<<"Alice Rendering..." <<std::endl;
	std::cout<<"Progress: "<<std::endl;

	r.Render(scene,"Ray.tga");
	image.SaveAsTga("SoraS.tga");

	std::cout.flush();
	std::cout<<std::endl<<std::endl;
	std::cout<<"Alice Render Finish." <<std::endl;
	system("pause");
	return 0;
}

