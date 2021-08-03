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

inline void calculateBallBoundariesY(Draw& draw, float yDim)
{
	draw.ball.top = yDim + draw.ball.centerY;
	draw.ball.bottom = -yDim + draw.ball.centerY;
}

inline void calculateBallBoundariesX(Draw& draw, float xDim)
{
	draw.ball.right = xDim + draw.ball.centerX;
	draw.ball.left = -xDim + draw.ball.centerX;
}

void updateBall(Draw& draw)
{
	// Should be moved to the draw class
	static bool directionRight = true;
	static bool directionUp = true;

	// Ball dimensions
	float xDim = 36.0f / width;
	float yDim = 36.0f / height;

	float ballYMax = 1 - (36.0f / (height / 2));
	float ballXMax = 1.0f;

	// Check if the ball should bounce off
	// If the ball escapes, which shouldn't happen, it will constantly change direction, 
	// which results in not coming back

	if (directionUp)
	{
		draw.ball.centerY += 0.01f;
		calculateBallBoundariesY(draw, yDim);
		if (draw.ball.top >= ballYMax - 0.0025f)
		{
			draw.ball.updateCenterYByTopPos(yDim, ballYMax);
			calculateBallBoundariesX(draw, yDim);
			directionUp = !directionUp;
		}
	}
	else
	{
		draw.ball.centerY -= 0.01f;
		calculateBallBoundariesY(draw, yDim);
		if (draw.ball.bottom <= -(ballYMax - 0.0025f))
		{
			draw.ball.updateCenterYByTopBottom(yDim, -ballYMax);
			calculateBallBoundariesX(draw, yDim);
			directionUp = !directionUp;
		}
	}

	if (draw.ball.right >= ballXMax || draw.ball.left <= -ballXMax)
		// Shouldn't bounce here, the player lost
		directionRight = !directionRight;

	// Move the ball in the right direction

	if (directionRight)
		draw.ball.centerX += 0.01f;
	else
		draw.ball.centerX -= 0.01f;

	calculateBallBoundariesX(draw, xDim);

	// Check if the ball should bounce of a paddle

	// TODO:
	// The ball doesn't bouce off the top or bottom, which it should.
	// Add left paddle, some if's could probably be done for both at the same time (?)

	if (draw.ball.right + 0.0025 >= draw.rightPaddle.left &&
		draw.ball.left <= draw.rightPaddle.right &&
		draw.ball.centerY <= draw.rightPaddle.top &&	// faulty
		draw.ball.centerY >= draw.rightPaddle.bottom)	// faulty
	{
		// The ball should bounce off the paddle
		// We align the ball to the paddle, so it looks pretty

		std::cout << "Hit!\n";
		directionRight = !directionRight;
		draw.ball.updateCenterXByTopRight(xDim, draw.rightPaddle.left);
		calculateBallBoundariesX(draw, xDim);
	}
}