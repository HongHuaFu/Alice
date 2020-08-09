#include "TestRayTracingCPU.hpp"

int main()
{
	using namespace Test::RayTracingCPU;
	// DrawHeart();
	// RayTracingInOneWeekendScene();
	RayTracingInOneWeekendSceneBVH();
	// RayTracingInOneWeekendSceneMotionBlur();

	system("pause");
	return 0;
}

