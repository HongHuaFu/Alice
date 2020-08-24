#include "TestRayTracingCPU.hpp"
#include "TestPathTracingCPU.hpp"

int main()
{
#pragma region RayTracingCPU
	using namespace Test::RayTracingCPU;
	// DrawHeart();
	// RayTracingInOneWeekendScene();
	// RayTracingInOneWeekendSceneBVH();
	// RayTracingInOneWeekendSceneMotionBlur();
	// RayTracingInOneWeekendSceneCheckerTexture();
	// RenderEarthTexture();
	// RenderEarthTexturePlaneLight();
	// EmptyCornellBox();
	// CornellBox();
	// CornellSmokeBox();
	// RayTracingNextWeekFinalScene();
#pragma endregion

#pragma region PathTracingCPU
	using namespace Alice::PathTracingCPU::UintTest;
	TVectorTest::MathRule();
#pragma endregion

	system("pause");
	return 0;
}

