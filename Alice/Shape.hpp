#pragma once
#include <Material.hpp>
#include <Math.hpp>
#include <Material.hpp>
#include <Ray.hpp>

namespace Alice
{
	// Base render object class.
	// It does not contain geometry information.
	// All detail geometry must derive from it.
	class Shape
	{
	public:
		Shape() = default;
		virtual ~Shape() = default;

		virtual Material* GetMaterial() const = 0;

		virtual bool Intersect(const Ray& ray) const = 0;
		virtual bool Intersect(const Ray& ray, glm::vec2&) const = 0;
		virtual bool Intersect(const Ray& ray, float&, uint32_t&,glm::vec2&) const = 0;

		virtual void GetSurfaceProperties(const glm::vec3&, const glm::vec3&, const uint32_t &, const glm::vec2&, glm::vec3&, glm::vec2&) const = 0;
		virtual glm::vec3 EvalDiffuseColor(const glm::vec2&) const =0;
	};
}