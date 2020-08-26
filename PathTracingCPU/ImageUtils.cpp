#include <PathTracingCPU/ImageUtils.hpp>
#include <stb_image.h>
#include <stb_image_write.h>

namespace Alice::PathTracingCPU::Tool
{
	std::pair<std::vector<Color3f>,Vector2i> MyImageTool::Load3Comp(std::string path)
	{
		std::vector<Color3f> data;
		Vector2i size;
		const static int bytes_per_pixel = 3;
		auto components_per_pixel = bytes_per_pixel;

		ALICE_TRACE_IO("Loading image on path: " + path + "...");
		auto raw_data = stbi_load(path.c_str(), &size.x, &size.y, &components_per_pixel, components_per_pixel);

		if (!raw_data)
		{
			std::cerr << "ERROR: Could not load texture image file '" << path << "'.\n";
			size.x = size.y = 0;
		}

		ALICE_ASSERT(components_per_pixel == 3, "Error image component nums!, this function only used to load rgb image! please check out!");

		data.resize((size_t)size.x * (size_t)size.y);

		size_t index = 0;
		for (size_t i = 0; i < (size_t)size.x * (size_t)size.y * components_per_pixel; i = i + components_per_pixel)
		{
			// Range 0-255
			data[index] = Color3f( (float)raw_data[i] / 255.f, (float)raw_data[i+1] / 255.f, (float)raw_data[i+2] / 255.f);
			index++;
		}
		ALICE_TRACE_IO("Finish loading image on path: " + path + "...");
		return std::make_pair(data, size);
	}

	void MyImageTool::Save3Comp(std::string path, Vector2i size, BitmapType type, const std::vector<Color3f>& colordata)
	{
		stbi_flip_vertically_on_write(true);
		ALICE_TRACE_IO("Saving image on path: " + path + "...");

		std::vector<unsigned char> data;
		data.resize((size_t)size.x * (size_t)size.y * 3);

		size_t r_i = 0;
		for (size_t i = 0; i < data.size(); i+= 3 )
		{
			data[i]   = (unsigned char)( glm::clamp(colordata[r_i].r() * 255.f,0.f,255.f));
			data[i+1] = (unsigned char)(glm::clamp(colordata[r_i].g() * 255.f,0.f,255.f));
			data[i+2] = (unsigned char)(glm::clamp(colordata[r_i].b() * 255.f,0.f,255.f));
			r_i++;
		}

		switch (type)
		{
		case Alice::PathTracingCPU::BitmapType::PNG:
		{
			stbi_write_png(path.c_str(), size.x, size.y, 3, &(data[0]), size.x * 3);
			break;
		}
		case Alice::PathTracingCPU::BitmapType::JPG:
		{
			stbi_write_jpg(path.c_str(), size.x, size.y, 3, &(data[0]),100);
			break;
		}
		case Alice::PathTracingCPU::BitmapType::TGA: 
		{
			stbi_write_tga(path.c_str(), size.x, size.y, 3, &(data[0]));
			break;
		}
		default: 
		{
			std::cerr << "ERROR: Unknow bitmap type.\n";
			exit(-1);
		}
		}
		ALICE_TRACE_IO("Finish saving image on path: " + path + "...");
	}
}