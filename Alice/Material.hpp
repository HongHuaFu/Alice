#pragma once
#include <Math.hpp>
#include <Image.hpp>

namespace Alice
{
	enum class MaterialType
	{
		DIFFUSE_AND_GLOSSY,
		REFLECTION_AND_REFRACTION,
		REFLECTION
	};

	class Material
	{
	public:
		MaterialType type = MaterialType::DIFFUSE_AND_GLOSSY;
		glm::vec3 color = glm::vec3(0.2f);
		glm::vec3 emission = glm::vec3(0);
		float ior = 1.3f,kd = 0.8f,ks = 0.2f;
		float specularExponent = 25.0f;

		Image* texture;
	public:
		Material() = default;

		auto GetType() const { return type; }
		auto GetColor() const { return color; }
		auto GetEmission() const {return emission; }

		// TODO: Add texture mapping.
		auto GetColorAt(float u,float v) const
		{
			if(texture == nullptr)
				return glm::vec3(0);

			return texture->GetPixel(u,v);
		}
	};
}