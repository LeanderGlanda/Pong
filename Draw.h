#pragma once

class Draw 
{
	int drawBackgroundImage(GLuint VAO);
	int drawOverlay(GLuint VAO);
	int drawPaddle(GLuint VAO);
	int drawBall(GLuint VAO);

public:
	GLuint VAO[4];
	int vertexCount[4];
	
	float rightPaddleY;

	struct Vertex
	{
		float x, y, z, r, g, b, a;
	};
	struct Rectangle
	{
		float top, bottom, right, left, centerY, centerX;
		inline void updateCenterYByTopPos(float yDim, float newTop)
		{
			top = newTop;
			centerY = top - yDim;
		}
		inline void updateCenterYByTopBottom(float yDim, float newBottom)
		{
			bottom = newBottom;
			centerY = bottom + yDim;
		}
	};

	Rectangle rightPaddle;
	Rectangle leftPaddle;
	Rectangle ball;

	void update();

	Draw();
	~Draw();
};