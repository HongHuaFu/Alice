#pragma once
#include <RayTracingCPU/Math.hpp>
#include <memory>

namespace Alice::RayTracingCPU
{
	class Texture
	{
	public:
		virtual vec3 Color(float u,float v,const vec3& p) const = 0;
	};

	class TextureSolidColor : public Texture 
	{
	protected:
		vec3 color_value;

	public:
		TextureSolidColor() {}
		TextureSolidColor(vec3 c) : color_value(c) {}

		TextureSolidColor(float red, float green, float blue)
			: TextureSolidColor(vec3(red,green,blue)) {}

		virtual vec3 Color(float u, float v, const vec3& p) const override {
			return color_value;
		}
	};

	class TextureCheckerTexture: public Texture
	{
	public:
		TextureCheckerTexture() {}

		TextureCheckerTexture(std::shared_ptr<Texture> t0, std::shared_ptr<Texture> t1)
			: even(t0), odd(t1) {}

		TextureCheckerTexture(vec3 c1, vec3 c2)
			: even(std::make_shared<TextureSolidColor>(c1)) , odd(std::make_shared<TextureSolidColor>(c2)) 
		{

		}

		virtual vec3 Color(float u, float v, const vec3& p) const override 
		{
			auto sines = sin(X_Num * p.x) * sin(Y_Num * p.y) * sin(Z_Num * p.z);
			if (sines < 0)
				return odd->Color(u, v, p);
			else
				return even->Color(u, v, p);
		}

	public:
		std::shared_ptr<Texture> odd;
		std::shared_ptr<Texture> even;
		// ∆Â≈Ã∏ÒX
		uint X_Num = 10;
		// ∆Â≈Ã∏ÒY
		uint Y_Num = 10;
		// ∆Â≈Ã∏ÒZ
		uint Z_Num = 10;
	};

	class TextureImage: public Texture
	{
	protected:
		float *data;
		int width, height;
		int bytes_per_scanline;

	public:
		const static int bytes_per_pixel = 3;

		TextureImage() : data(nullptr), width(0), height(0), bytes_per_scanline(0) {}

		TextureImage(const char* filename);

		~TextureImage() 
		{
			delete data;
		}

		virtual vec3 Color(float u, float v, const vec3& p) const override 
		{
			if (data == nullptr)
				return vec3(0,1.0f,1.0f);

			u = clamp(u, 0.0f, 1.0f);
			v = 1.0 - clamp(v, 0.0f, 1.0f);  

			auto i = static_cast<int>(u * width);
			auto j = static_cast<int>(v * height);

			if (i >= width)  i = width-1;
			if (j >= height) j = height-1;


			auto pixel = data + j * bytes_per_scanline + i * bytes_per_pixel;

			return vec3(pixel[0],pixel[1], pixel[2]);
		}
	};
}

