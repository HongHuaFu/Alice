#pragma once
#include <Math.hpp>
#include <Shape.hpp>
#include <memory>
#include <Core.hpp>
#include <cstring>

namespace Alice
{
	bool RayTriangleIntersect(const glm::vec3& v0, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& orig,const glm::vec3& dir, float& tnear, float& u, float& v)
	{
		auto e1 = v1 - v0;
		auto e2 = v2 - v0;
		auto s = orig - v0;
		auto s1 = glm::cross(dir,e2);
		auto s2 = glm::cross(s,e1);
		auto s1e1 = 1 / glm::dot(s1,e1);
		auto t = glm::dot(s2,e2) * s1e1;
		auto b1 = glm::dot(s1,s) * s1e1;
		auto b2 = glm::dot(s2,dir) * s1e1;

		if(t > 0 && b1 > 0 && b2 > 0 && 1 - b1 -b2 > 0)
		{
			tnear = t;
			u = b1;
			v = b2;
		    return true;
		}
		return false;
	}

	class Triangle final: public Shape
	{
	public:
		// vertices A, B ,C , counter-clockwise order
		glm::vec3 v0, v1, v2; 
		// 2 edges v1-v0, v2-v0;
		glm::vec3 e1, e2;     
		// texture coords
		glm::vec2 t0, t1, t2;
		glm::vec3 normal;
		Material* material;

	public:
		Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, Material* _m = nullptr)
			: v0(_v0), v1(_v1), v2(_v2), material(_m)
		{
			e1 = normalize(v1 - v0);
			e2 = normalize(v2 - v0);
			normal = normalize(glm::cross(e1, e2));
		}

		Material* GetMaterial() const override
		{
			return material;
		}

		bool Intersect(const Ray& ray) const override
		{
			bool intersect = false;
			float t, u, v;
			if (RayTriangleIntersect(v0, v1, v2, ray.origin, ray.direction, t, u, v))
			{
				intersect = true;
			}
			return intersect;
		}

		bool Intersect(const Ray& ray,glm::vec2& uv) const override
		{
			bool intersect = false;
			float t, u, v;
			if (RayTriangleIntersect(v0, v1, v2, ray.origin, ray.direction, t, u, v))
			{
				uv.x = u;
				uv.y = v;
				intersect = true;
			}
			return intersect;
		}

		bool Intersect(const Ray& ray,float& tnear,uint32_t& index,glm::vec2& uv) const override
		{
			bool intersect = false;
			float t, u, v;
			if (RayTriangleIntersect(v0, v1, v2, ray.origin, ray.direction, t, u, v))
			{
				tnear = t;
				uv.x = u;
				uv.y = v;
				intersect = true;
			}
			return intersect;
		}

		void GetSurfaceProperties(const glm::vec3&, const glm::vec3&, const uint32_t& index, const glm::vec2& uv, glm::vec3& N, glm::vec2& st) const override
		{
			N = normal;
			st = t0 * (1 - uv.x - uv.y) + t1 * uv.x + t2 * uv.y;
		}

		// TODO: Add Texture Mapping
		glm::vec3 EvalDiffuseColor(const glm::vec2& st) const override
		{
			return glm::vec3(st.x,0,0);

			// return EvalDiffuseColorPattern(st);	
			// return material->GetColorAt(st.x,st.y);
		}

		glm::vec3 EvalDiffuseColorPattern(const glm::vec2& st) const
		{
			float scale = 5.0f;
			float pattern = (fmodf(st.x * scale, 1.0f) > 0.5f) ^ (fmodf(st.y * scale, 1.0f) > 0.5f);
			return glm::lerp(glm::vec3(0.815f, 0.235f, 0.031f), glm::vec3(0.937f, 0.937f, 0.231f), pattern);
		}


	};

	class MeshTriangle final : public Shape
	{
	public:
		std::vector<glm::vec3> vertices;
		uint32_t numTriangles;
		std::vector<uint32_t> vertexIndex;
		std::vector<glm::vec2> stCoordinates;
		Material* material;
	public:
		MeshTriangle(const glm::vec3* verts, const uint32_t* vertsIndex, const uint32_t& numTris, const glm::vec2* st,Material* m)
		{
			uint32_t maxIndex = 0;
			for (uint32_t i = 0; i < numTris * 3; ++i)
				if (vertsIndex[i] > maxIndex)
					maxIndex = vertsIndex[i];
			maxIndex += 1;

			vertices.resize(maxIndex);
			memcpy(&vertices[0], verts, sizeof(glm::vec3) * maxIndex);
			vertexIndex.resize(numTris * 3);
			memcpy(&vertexIndex[0], vertsIndex, sizeof(uint32_t) * numTris * 3);
			numTriangles = numTris;
			stCoordinates.resize(maxIndex);
			memcpy(&stCoordinates[0], st, sizeof(glm::vec2) * maxIndex);
			material = m;
		}

		bool Intersect(const Ray& ray) const override { return false;}
		bool Intersect(const Ray& ray, glm::vec2&) const override { return false;}

		bool Intersect(const Ray& ray, float& tnear, uint32_t& index, glm::vec2& uv) const override
		{
			bool intersect = false;
			for (uint32_t k = 0; k < numTriangles; ++k)
			{
				auto v0 = vertices[vertexIndex[k * 3]];
				auto v1 = vertices[vertexIndex[k * 3 + 1]];
				auto v2 = vertices[vertexIndex[k * 3 + 2]];
				float t, u, v;
				if (RayTriangleIntersect(v0, v1, v2, ray.origin, ray.direction, t, u, v) && t < tnear)
				{
					tnear = t;
					uv.x = u;
					uv.y = v;
					index = k;
					intersect |= true;
				}
			}
			return intersect;
		}

		void GetSurfaceProperties(const glm::vec3&, const glm::vec3&, const uint32_t& index, const glm::vec2& uv, glm::vec3& N, glm::vec2& st) const override
		{
			auto v0 = vertices[vertexIndex[index * 3]];
			auto v1 = vertices[vertexIndex[index * 3 + 1]];
			auto v2 = vertices[vertexIndex[index * 3 + 2]];
			auto e0 = normalize(v1 - v0);
			auto e1 = normalize(v2 - v1);
			N = normalize(glm::cross(e0, e1));
			auto st0 = stCoordinates[vertexIndex[index * 3]];
			auto st1 = stCoordinates[vertexIndex[index * 3 + 1]];
			auto st2 = stCoordinates[vertexIndex[index * 3 + 2]];
			st = st0 * (1 - uv.x - uv.y) + st1 * uv.x + st2 * uv.y;
		}

		glm::vec3 EvalDiffuseColor(const glm::vec2& st) const override
		{
			if(material == nullptr)
				return glm::vec3(0);
			return material->GetColorAt(st.x,st.y);
		}

		Material* GetMaterial() const override { return material; }

	};

}

