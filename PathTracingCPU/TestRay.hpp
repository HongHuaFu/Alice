#pragma once
#include <PathTracingCPU/Core.hpp>
#include <PathTracingCPU/Ray.hpp>
#include <PathTracingCPU/Vector.hpp>
#include <PathTracingCPU/Color.hpp>

namespace Alice::PathTracingCPU::UintTest
{
	inline static bool RayConstructTest() 
	{
		auto r = TRay<Point3f, Vector3f>({ 0,0,0 }, { 1.0f,2.0f,0.0f }, 0.0001f, 99999.0f);
		std::cout << ToString(r) << std::endl;
		std::cout << ToString(r.dRcp) << std::endl;
		auto color = Color4f(1.0f, 1.0f, 2.0f, 1.0f);
		std::cout << ToString(color) << std::endl;

		return true;
	}
}