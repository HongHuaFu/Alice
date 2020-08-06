#pragma once
#include <Math.hpp>

namespace Alice
{
	class Random
	{
	public:
		static float GetRandom1d(float min = -1.0f,float max = 1.0f){ return linearRand(min,max); }

		// ��������ڵ������λ����
		static vec2 GetRandom2d(float min = -1.0f,float max = 1.0f){ return vec2(GetRandom1d(min,max),GetRandom1d(min,max)); }

		// ��������ڵ������λ����
		static vec3 GetRandom3d(float min = -1.0f,float max = 1.0f){ return vec3(GetRandom1d(min,max),GetRandom1d(min,max),GetRandom1d(min,max)); }

		// �������ĵ�λ���� 2d
		static vec2 GetRandom2dUint(){ return normalize(GetRandom2d()); }

		// �������ĵ�λ���� 3d
		static vec3 GetRandom3dUint(){ return normalize(GetRandom3d()); }
	};
}