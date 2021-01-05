#include "Main.h"

bool paddleDirectionUp = true;

void updatePaddle(Draw& draw)
{
	float yOffsetMax = 1 - (36.0f / (height / 2)) - 144.0f / height;
	if (paddleDirectionUp)
	{
		draw.yOffset += 0.01f;
		if (draw.yOffset > yOffsetMax)
		{
			paddleDirectionUp = false;
			draw.yOffset = yOffsetMax;
		}
	}
	else
	{
		draw.yOffset -= 0.01f;
		if (draw.yOffset - 0.01f < -yOffsetMax)
		{
			paddleDirectionUp = true;
			draw.yOffset = -yOffsetMax;
		}
	}
	std::cout << draw.yOffset << "\n";
}