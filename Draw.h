#pragma once

class Draw 
{
	int drawBackgroundImage(GLuint VAO);
	int drawOverlay(GLuint VAO);
	int drawPaddle(GLuint VAO);

public:
	GLuint VAO[3];
	int vertexCount[3];
	float yOffset;

	struct Vertex;

	void update();

	Draw();
	~Draw();
};