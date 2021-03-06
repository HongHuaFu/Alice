#pragma once
#include <RayTracingCPU/Math.hpp>

namespace Alice::RayTracingCPU
{
	class Random
	{
	public:
		static float GetRandom1d(float min = -1.0f,float max = 1.0f){ return linearRand(min,max); }

		static int GetRandom1dInt(int min = -1,int max = 1){ return static_cast<int>(GetRandom1d(static_cast<float>(min),static_cast<float>(max + 1))); }

		// 获得区间内的随机单位向量
		static vec2 GetRandom2d(float min = -1.0f,float max = 1.0f){ return vec2(GetRandom1d(min,max),GetRandom1d(min,max)); }

		// 获得区间内的随机单位向量
		static vec3 GetRandom3d(float min = -1.0f,float max = 1.0f){ return vec3(GetRandom1d(min,max),GetRandom1d(min,max),GetRandom1d(min,max)); }

		// 获得随机的单位向量 2d
		static vec2 GetRandom2dUint(){ return normalize(GetRandom2d()); }

		// 获得随机的单位向量 3d
		static vec3 GetRandom3dUint(){ return normalize(GetRandom3d()); }
	};
}