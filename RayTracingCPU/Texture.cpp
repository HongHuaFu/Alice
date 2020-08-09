#include <RayTracingCPU/Texture.hpp>
#include <stb_image.h>
#include <iostream>

namespace Alice::RayTracingCPU
{
	TextureImage::TextureImage(const char* path)
	{
		auto components_per_pixel = bytes_per_pixel;
		auto raw_data = stbi_load( path, &width, &height, &components_per_pixel, components_per_pixel);

		if (!raw_data) 
		{
			std::cerr << "ERROR: Could not load texture image file '" << path << "'.\n";
			width = height = 0;
		}

		data = new float[width * height * components_per_pixel];
		for(size_t i = 0; i<width * height * components_per_pixel; i = i + components_per_pixel)
		{
			data[i] = std::pow((float) raw_data[i] * (1/255.0f), 2.2f);
			data[i+1] = std::pow((float) raw_data[i + 1] * (1/255.0f), 2.2f);
			data[i + 2] = std::pow((float) raw_data[i + 2] * (1/255.0f), 2.2f);
		}

		bytes_per_scanline = bytes_per_pixel * width;
	}
}