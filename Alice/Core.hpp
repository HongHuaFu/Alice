#pragma once
#include <iostream>

namespace Alice
{
    constexpr auto EPSILON = 0.00001f;

	inline void PrintRenderProgress(float progress)
	{
		int barWidth = 100;
		std::cout << "|";
		int pos = (int)(barWidth * progress);
		for (int i = 0; i < barWidth; ++i)
		{
			if (i < pos)
				std::cout << "-";
			else if (i == pos)
				std::cout << ">";
			else
				std::cout << " ";
		}
		std::cout << "| " << progress * 100.0f << " %\r";
		std::cout.flush();
	}
}