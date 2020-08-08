#pragma once
#include <Math.hpp>
#include <Ray.hpp>

namespace Alice
{
	class Camera
	{
	private:
		// 相机放置点
		vec3 origin;
		// 幕布左下角点
		vec3 canvas_low_left_corner;
		// 幕布水平方向，竖直方向
		vec3 horizontal_dir,vertical_dir;
		vec3 u,v,w;
		float lens_radius;
		float time0,time1;// 相机开启/关闭的时间

	public:
		// lookfrom 视点
		// lookat 视线方向
		// vup 空间中向上向量，用于施密特正交化
		// vfov 视角
		// aspect 长宽比
		// aperture 光圈大小
		// focus_dist 焦距
		Camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist,float t0 = 0,float t1 = 0);
		
		// 投射光线
		Ray CastRay(const vec2& uv) const { return CastRay(uv.x,uv.y); }
		Ray CastRay(float u,float v) const;
	};
}