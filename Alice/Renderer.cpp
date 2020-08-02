#include <Renderer.hpp>
#include <Shape.hpp>
#include <optional>
#include <Color.hpp>
#include <Core.hpp>
#include <Image.hpp>
#include <Hit.hpp>
#include <Ray.hpp>

namespace Alice
{
	auto Trace(const Ray& ray,const std::vector<Shape*>& shapes)
	{
		float tNear = std::numeric_limits<float>::max();
		std::optional<Hit> hit;
		uint32_t index;
		for (const auto & shape : shapes)
		{
			glm::vec2 uv = glm::vec2(0);
			if (shape->Intersect(ray,tNear,index,uv))
			{
				hit.emplace();
				hit->hitShape = shape;
				hit->uv = uv;
				hit->tNear = tNear;
			}
		}
		return hit;
	}

	auto CastRay(const glm::vec3& orig, const  glm::vec3& dir, const Scene& scene,int depth)
	{
		if (depth > scene.maxDepth) {
			return glm::vec3(0.0,0.0,0.0);
		}

		glm::vec3 hitColor = scene.backgroundColor;
		Ray ray(orig,dir);
		if (auto hit = Trace(ray, scene.GetShapes()); hit)
		{
			glm::vec3 hitPoint = orig + dir * hit->tNear;
			glm::vec3 N;
			glm::vec2 st;
			hit->hitShape->GetSurfaceProperties(hitPoint, dir, hit->index, hit->uv, N, st);
			switch (hit->hitShape->GetMaterial()->GetType()) {
			case MaterialType::REFLECTION_AND_REFRACTION:
			{
				glm::vec3 reflectionDirection = glm::normalize(reflect(dir, N));
				glm::vec3 refractionDirection = glm::normalize(Refract(dir, N, hit->hitShape->GetMaterial()->ior));
				glm::vec3 reflectionRayOrig = (glm::dot(reflectionDirection, N) < 0) ?
					hitPoint - N * scene.epsilon : hitPoint + N * scene.epsilon;
				glm::vec3 refractionRayOrig = (glm::dot(refractionDirection, N) < 0) ?
					hitPoint - N * scene.epsilon : hitPoint + N * scene.epsilon;
				glm::vec3 reflectionColor = CastRay(reflectionRayOrig, reflectionDirection, scene, depth + 1);
				glm::vec3 refractionColor = CastRay(refractionRayOrig, refractionDirection, scene, depth + 1);
				float kr = Fresnel(dir, N, hit->hitShape->GetMaterial()->ior);
				hitColor = reflectionColor * kr + refractionColor * (1 - kr);
				break;
			}
			case MaterialType::REFLECTION:
			{
				float kr = Fresnel(dir, N, hit->hitShape->GetMaterial()->ior);
				glm::vec3 reflectionDirection = reflect(dir, N);
				glm::vec3 reflectionRayOrig = (glm::dot(reflectionDirection, N) < 0) ?
					hitPoint + N * scene.epsilon :
					hitPoint - N * scene.epsilon;
				hitColor = CastRay(reflectionRayOrig, reflectionDirection, scene, depth + 1) * kr;
				break;
			}
			default:
			{
				glm::vec3 lightAmt = glm::vec3(0), specularColor = glm::vec3(0);
				glm::vec3 shadowPointOrig = (glm::dot(dir, N) < 0) ?
					hitPoint + N * scene.epsilon :
					hitPoint - N * scene.epsilon;
				for (auto& light : scene.GetLights()) {
					auto lightDir = light->GetPosition() - hitPoint;
					float lightDistance2 = glm::dot(lightDir, lightDir);
					lightDir = normalize(lightDir);
					float LdotN = std::max(0.f, glm::dot(lightDir, N));
					auto shadow_res = Trace( Ray(shadowPointOrig, lightDir), scene.GetShapes());
					bool inShadow = shadow_res && (shadow_res->tNear * shadow_res->tNear < lightDistance2);

					lightAmt += inShadow ? glm::vec3(0) : light->GetIntensity() * LdotN;
					auto reflectionDirection = reflect(-lightDir, N);

					specularColor += powf(std::max(0.f, -glm::dot(reflectionDirection, dir)),
						hit->hitShape->GetMaterial()->specularExponent) * light->GetIntensity();
				}

				hitColor = lightAmt * hit->hitShape->EvalDiffuseColor(st) * hit->hitShape->GetMaterial()->kd + specularColor * hit->hitShape->GetMaterial()->ks;
				break;
			}
			}
		}

		return hitColor;
	}

	void Renderer::Render(const Scene& scene,const std::string& path)
	{
		std::vector<Color> framebuffer(scene.width * scene.height);

		float scale = std::tan(glm::radians(scene.fov * 0.5f));
		float imageAspectRatio = scene.width / (float)scene.height;

		// Use this variable as the eye position to start your rays.
		glm::vec3 eye_pos(0);
		int m = 0;
		for (int j = 0; j < scene.height; ++j)
		{
			for (int i = 0; i < scene.width; ++i)
			{
				// generate primary ray direction
				float x = ( (float)i / (float)scene.width - 0.5f) * imageAspectRatio * scale;
				float y = ( (float)j / (float)scene.height - 0.5f) * scale;

				glm::vec3 dir = normalize(glm::vec3(x, y, -1.0f)); 
				auto res = CastRay(eye_pos, dir, scene, 0);

				framebuffer[m].r = unsigned char(res.x * 255);
				framebuffer[m].g = unsigned char(res.y * 255);
				framebuffer[m].b = unsigned char(res.z * 255);
				m++;
			}
			PrintRenderProgress(j / (float)scene.height);
		}

		Image ret(scene.width,scene.height,3,framebuffer.data());
		ret.SaveAsTga(path);
	}
}