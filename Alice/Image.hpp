#pragma once
#include <vector>
#include <string>
#include <Math.hpp>

namespace Alice
{
	// Image class contain framebuffer data,
	// We Can use it as a fbo but no care of assume.
	class Image
	{
	public:
		inline auto GetWidth() const { return width; }
		inline auto GetHeight() const { return height; }
		inline auto GetChannel() const { return channel; }
		inline auto GetData() const { return data; }

		explicit Image(uint32_t w,uint32_t h,uint32_t c,const unsigned char* d)
		: width(w),height(h),channel(c)
		{
			auto size = width * height * channel;
			data.resize(size);
			memcpy(&data[0],d,sizeof(unsigned char) * size);
		}

		Image() = default;
		~Image() = default;

		bool SetPixel(uint32_t x,uint32_t y,unsigned char r,unsigned char g,unsigned char b);
		bool SetPixel(uint32_t x,uint32_t y,Color color);
		int SaveAsTga(std::string path);

	private:
		uint32_t width,height,channel;
		std::vector<unsigned char> data;
	};

	// Image load function.
	Image ImageLoad(std::string path,int req_comp = 0);

	// Image save function.
	int ImageSave(Image* image,std::string path);


	// Only for test.
	// Draw a 3d heart and use phong shading model.
	int ImageDrawHeartTest(std::string path = "heart.tga",uint32_t width = 512,uint32_t height = 512);

	// Only for test.
	// Draw a box to check image write position is true.
	int ImageDrawBoxTest(std::string path = "box.tga",uint32_t width = 512,uint32_t height = 256);
}