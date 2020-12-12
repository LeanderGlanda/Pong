#include "Main.h"

int setupBackgroundImage(GLuint VAO)
{
	// create the vertices and the indices
	float vertices[] = {
		// positions          // colors        
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, // top right
		 1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f, // bottom right
		-1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f, // bottom left
		-1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f, // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	GLuint VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return sizeof(indices) / 4;
}

int setupOverlay(GLuint VAO)
{
	// create the vertices and the indices
	float vertices[] = {
		// positions          // colors        
		 1.0f,  1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // top top right
		 1.0f,  0.9f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // top bottom right
		-1.0f,  0.9f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // top bottom left
		-1.0f,  1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // top top left 

		 1.0f, -0.9f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // bottom top right
		 1.0f, -1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // bottom bottom right
		-1.0f, -1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // bottom bottom left
		-1.0f, -0.9f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f, // bottom top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
		4, 5, 7, // third triangle
		5, 6, 7  // fourth triangle
	};

	GLuint VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	return sizeof(indices) / 4;
}