#pragma once
#include <Scene.hpp>
#include <string>

namespace Alice
{
	class Renderer
	{
	public:
		void Render(const Scene& scene,const std::string& path);
	};
}