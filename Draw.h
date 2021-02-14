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
	float ballCordX;
	float ballCordY;

	struct Vertex;

	void update();

	Draw();
	~Draw();
};