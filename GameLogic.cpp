#include "Main.h"

bool rightPaddleDirectionUp = true;

void updateRightPaddle(Draw& draw, GLFWwindow* window)
{
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	float rightPaddleYMax = 1 - (36.0f / (height / 2)) - 144.0f / height;
	float rightPaddleY = 1 - ((float)ypos * 2 / (height));

	if (rightPaddleY > rightPaddleYMax)
		rightPaddleY = rightPaddleYMax;
	else if (rightPaddleY < -rightPaddleYMax)
		rightPaddleY = -rightPaddleYMax;

	// Set the coords of the paddle
	// Used for drawing
	
	float xDim = 72.0f / width;
	float yDim = 144.0f / height;

	draw.rightPaddle.right = 1.0f - 18.0f / width;
	draw.rightPaddle.left = 1.0f - 18.0f / width - xDim;
	draw.rightPaddle.top = yDim + rightPaddleY;
	draw.rightPaddle.bottom = -yDim + rightPaddleY;

	// No different height calculations for left paddle right now, so we set its coords here

	draw.leftPaddle.right = 18.0f / width - 1.0f;
	draw.leftPaddle.left = 18.0f / width + xDim - 1.0f;
	draw.leftPaddle.top = yDim + rightPaddleY;
	draw.leftPaddle.bottom = -yDim + rightPaddleY;

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
		draw.ballCordX += 0.01f;
	else
		draw.ballCordX -= 0.01f;

	if (directionUp)
		draw.ballCordY += 0.01f;
	else
		draw.ballCordY -= 0.01f;

	// Calcuate drawing positions of ball

	float xDim = 36.0f / width;
	float yDim = 36.0f / height;

	draw.ball.right = xDim + draw.ballCordX;
	draw.ball.left = -xDim + draw.ballCordX;
	draw.ball.top = yDim + draw.ballCordY;
	draw.ball.bottom = -yDim + draw.ballCordY;
}