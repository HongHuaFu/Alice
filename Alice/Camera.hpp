#pragma once
#include <Math.hpp>
#include <Ray.hpp>

namespace Alice
{
	class Camera
	{
	private:
		// ������õ�
		vec3 origin;
		// Ļ�����½ǵ�
		vec3 canvas_low_left_corner;
		// Ļ��ˮƽ������ֱ����
		vec3 horizontal_dir,vertical_dir;
		vec3 u,v,w;
		float lens_radius;
		float time0,time1;// �������/�رյ�ʱ��

	public:
		// lookfrom �ӵ�
		// lookat ���߷���
		// vup �ռ�����������������ʩ����������
		// vfov �ӽ�
		// aspect �����
		// aperture ��Ȧ��С
		// focus_dist ����
		Camera(vec3 lookfrom,vec3 lookat,vec3 vup,float vfov,float aspect,float aperture,float focus_dist,float t0 = 0,float t1 = 0);
		
		// Ͷ�����
		Ray CastRay(const vec2& uv) const { return CastRay(uv.x,uv.y); }
		Ray CastRay(float u,float v) const;
	};
}