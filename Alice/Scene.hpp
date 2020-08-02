#pragma once
#include <vector>
#include <memory>
#include <Math.hpp>
#include <Shape.hpp>
#include <Light.hpp>

namespace Alice
{
	class Scene
	{
	public:
		int width = 1280;
		int height = 960;
		float fov = 90.0f;
		glm::vec3 backgroundColor = glm::vec3(0.235294f,0.67451f,0.843137f);
		int maxDepth = 5;
		float epsilon = 0.00001f;

	private:
		std::vector<Shape*> shapes;
		std::vector<Light*> lights;
	
	public:
		Scene(int w, int h) : width(w), height(h){ }

		// Scene class doesn't manage shape and light 's destroy.
		~Scene() = default;

		void AddShapeReference(Shape* shape) { shapes.push_back(shape); }
		void AddLightReference(Light* light) { lights.push_back(light); }

		const std::vector<Shape*>& GetShapes() const { return shapes; }
		const std::vector<Light*>& GetLights() const { return lights; }
	};
}

