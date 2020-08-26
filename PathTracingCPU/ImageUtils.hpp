#pragma once
#include <PathTracingCPU/Vector.hpp>
#include <PathTracingCPU/Color.hpp>
#include <PathTracingCPU/Texture.hpp>
#include <string>
#include <vector>

namespace Alice::PathTracingCPU::Tool 
{
	class MyImageTool 
	{
	public:
		static std::pair<std::vector<Color3f>, Vector2i> Load3Comp(std::string path);
		static void Save3Comp(std::string filepath, Vector2i size, BitmapType type, const std::vector<Color3f>& data);
	};
}