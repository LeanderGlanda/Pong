#include "Main.h"

bool rightPaddleDirectionUp = true;

void updateRightPaddle(Draw& draw)
{
	float yOffsetMax = 1 - (36.0f / (height / 2)) - 144.0f / height;
	if (rightPaddleDirectionUp)
	{
		draw.yOffset += 0.01f;
		if (draw.yOffset > yOffsetMax)
		{
			rightPaddleDirectionUp = false;
			draw.yOffset = yOffsetMax;
		}
	}
	else
	{
		draw.yOffset -= 0.01f;
		if (draw.yOffset - 0.01f < -yOffsetMax)
		{
			rightPaddleDirectionUp = true;
			draw.yOffset = -yOffsetMax;
		}
	}
	std::cout << "Right paddle: " << draw.yOffset << "\n";
}