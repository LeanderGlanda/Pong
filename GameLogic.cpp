#include "Main.h"

bool rightPaddleDirectionUp = true;

void updateRightPaddle(Draw& draw)
{
	float rightPaddleYMax = 1 - (36.0f / (height / 2)) - 144.0f / height;
	if (rightPaddleDirectionUp)
	{
		draw.rightPaddleY += 0.01f;
		if (draw.rightPaddleY > rightPaddleYMax)
		{
			rightPaddleDirectionUp = false;
			draw.rightPaddleY = rightPaddleYMax;
		}
	}
	else
	{
		draw.rightPaddleY -= 0.01f;
		if (draw.rightPaddleY - 0.01f < -rightPaddleYMax)
		{
			rightPaddleDirectionUp = true;
			draw.rightPaddleY = -rightPaddleYMax;
		}
	}
	//std::cout << "Right paddle: " << draw.rightPaddleY << "\n";
}

void updateBall(Draw& draw)
{
	
}