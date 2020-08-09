#include <RayTracingCPU/Camera.hpp>
#include <RayTracingCPU/Random.hpp>

namespace Alice::RayTracingCPU
{
	Camera::Camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist,float t0,float t1)
	{
		lens_radius = aperture * 0.5f;
		float theta = vfov * pi<float>() / 180.0f;
		float half_height = tan(theta * 0.5f);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = normalize(lookfrom - lookat);
		u = normalize(cross(vup, w));
		v = cross(w, u);
		canvas_low_left_corner = origin  - half_width * focus_dist * u -half_height * focus_dist * v - focus_dist * w;
		horizontal_dir = 2 * half_width * focus_dist * u;
		vertical_dir = 2 * half_height  *focus_dist * v;

		if(t0 <= t1)
		{ 
			time0 = t0;
			time1 = t1;
		} 
		else
		{ 
			time0 = t1;
			time1 = t0;
		}
	}

	Ray Camera::CastRay(float u,float v) const
	{
		vec2 rd = lens_radius * Random::GetRandom2dUint();

		// 添加随机偏移
		vec3 offset = vec3(u * rd.x + v * rd.y);

		vec3 res_origin = origin + offset;
		vec3 res_dir = canvas_low_left_corner + u * horizontal_dir + v * vertical_dir - origin - offset;

		// 相机开启时间内随机产生射线
		return Ray(res_origin, res_dir,Random::GetRandom1d(time0,time1));
	}
}


