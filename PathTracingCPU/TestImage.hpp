#pragma once
#include <PathTracingCPU/Texture.hpp>

namespace Alice::PathTracingCPU::UintTest
{
	inline static bool TextureLoadAndSave()
	{
		auto c = Texture("./Asset/Textures/2k_earth_daymap.jpg");
		std::cout << ToString(c.size) << std::endl;
		c.Save("aa.jpg", BitmapType::JPG);
		return true;
	}
}