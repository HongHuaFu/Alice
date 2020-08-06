#include <Image.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>
#include <iostream>

namespace Alice::Privete
{
	float HeartCurveF(float x,float y,float z)
	{
		auto a = x * x + 9.0f /4.0f * y * y + z * z - 1;
		return a * a * a - x * x * z * z * z - 9.0f / 80.0f * y * y * z * z * z;
	}

	float HeartH(float x,float z)
	{
		for(float y = 1.0f; y >= 0.0f; y -= 0.0001f)
		{
			if(HeartCurveF(x,y,z) <= 0.0f)
			return y;
		}
		return 0.0f;
	}
}
namespace Alice
{
	bool Image::SetPixel(uint32_t x,uint32_t y,unsigned char r,unsigned char g,unsigned char b)
	{
		if(x >= width || y >= height)
			return false;
		data[y * width * channel + x * channel] = r;
		data[y * width * channel + x * channel + 1] = g;
		data[y * width * channel + x * channel + 2] = b;
		return true;
	}

	int Image::SaveAsTga(std::string path)
	{
		stbi_flip_vertically_on_write(true);
		return stbi_write_tga(path.c_str(),width,height,channel,&(data[0]));
	}

	Image ImageLoad(std::string path,int req_comp)
	{
		int x, y, n;
		stbi_set_flip_vertically_on_load(true);
		auto data = stbi_load(path.c_str(), &x, &y, &n,req_comp);
		if (req_comp != 0 && n > req_comp)
			n = req_comp;
		if (nullptr == data)
		{
			std::cout << "Can't open the file." << path <<std::endl;
			exit(-1);
		}
		Image image(x, y, n, data);
		return image;
	}

	int ImageSave(Image* image,std::string path)
	{
		if(image==nullptr)
		{
			std::cout << "Can't save nullptr file." << path <<std::endl;
			exit(-1);
		}
		return image->SaveAsTga(path);
	}

	int ImageDrawHeartTest(std::string path,uint32_t width,uint32_t height)
	{
		using namespace Alice::Privete;
		std::vector<unsigned char> data;
		data.resize(width * height * 3);
		Image ret(width,height,3,data.data());
		for(uint32_t sy = 0; sy < height; sy++)
		{
			float z = - ( 1.5f - sy * 3.0f / height);
			for(uint32_t sx = 0; sx < width; sx++)
			{
				float x = sx * 3.0f / width - 1.5f;
				float v = HeartCurveF(x,0.0f,z);
				int r = 0;
				if(v <= 0.0f)
				{
					float y0 = HeartH(x,z);
					float ny = 0.001f;
					float nx =  HeartH(x + ny,z) - y0;
					float nz =  HeartH(x,z + ny) - y0;
					float nd = 1.0f / sqrtf(nx * nx + ny * ny + nz * nz);
					float d = (nx + ny  - nz) /sqrtf(3) * nd * 0.5f + 0.5f;
					r = (unsigned char)(d * 255.0f);
					ret.SetPixel(sx,sy,r,0,0);
				}
			}
		}
		return ret.SaveAsTga(path);
	}

	int ImageDrawBoxTest(std::string path,uint32_t width,uint32_t height)
	{
		std::vector<unsigned char> data;
		data.resize(width * height * 3);
		Image ret(width,height,3,data.data());
		for(uint32_t x = 0; x < width; x++)
		{
			for(uint32_t y = 0; y < height; y++)
			{
				if(x < width / 4 && y < height / 5)
				{
					ret.SetPixel(x,y,255,0,0);
				}
			}
		}
		return ret.SaveAsTga(path);
	}
}

