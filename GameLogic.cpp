#include "Main.h"

bool rightPaddleDirectionUp = true;

void updateRightPaddle(Draw& draw, GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float rightPaddleYMax = 1 - (36.0f / (height / 2)) - 144.0f / height;

	draw.rightPaddleY = 1 - (ypos * 2 / (height));

	if (draw.rightPaddleY > rightPaddleYMax)
		draw.rightPaddleY = rightPaddleYMax;
	else if (draw.rightPaddleY < -rightPaddleYMax)
		draw.rightPaddleY = -rightPaddleYMax;
	/*if (rightPaddleDirectionUp)
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
	}*/
	//std::cout << "Right paddle: " << draw.rightPaddleY << "\n";
}

void updateBall(Draw& draw)
{
	// Should be moved to the draw class
	static bool directionRight = true;
	static bool directionUp = true;

	float ballYMax = 1 - (36.0f / (height / 2)) - 36.0f / height;
	float ballXMax = 1.0f;

	// Check if the ball should bounce off
	// If the ball escapes, which shouldn't happen, it will constantly change direction, 
	// which results in not coming back

	if (draw.ballCordY >= ballYMax || draw.ballCordY <= -ballYMax)
		directionUp = !directionUp;

	if (draw.ballCordX >= ballXMax || draw.ballCordX <= -ballXMax)
		// Shouldn't bounce here, the player lost
		directionRight = !directionRight;

	// Move the ball in the right direction

	if (directionRight)
		draw.ballCordX += 0.01;
	else
		draw.ballCordX -= 0.01;

	if (directionUp)
		draw.ballCordY += 0.01;
	else
		draw.ballCordY -= 0.01;
}