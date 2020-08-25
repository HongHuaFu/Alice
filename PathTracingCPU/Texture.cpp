#include <PathTracingCPU/Texture.hpp>
#include <PathTracingCPU/ImageUtils.hpp>

namespace Alice::PathTracingCPU
{
	Texture::Texture(const std::string& filename)
	{
		auto res = Tool::MyImageTool::Load3Comp(filename);
		colorData = res.first;
		size = res.second;
	}

	void Texture::Save(const std::string& filename, BitmapType type)
	{
		Tool::MyImageTool::Save3Comp(filename, size, type, colorData);
	}
}
