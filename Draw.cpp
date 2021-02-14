#include "Main.h"

struct Draw::Vertex
{
	float x, y, z, r, g, b, a;
};

Draw::Draw()
{
	glGenVertexArrays(4, VAO);
	vertexCount[0] = 0;
	vertexCount[1] = 0;
	vertexCount[2] = 0;
	vertexCount[3] = 0;
	rightPaddleY = 0.0f;
	ballCordX = 0.0f;
	ballCordY = 0.0f;
}
Draw::~Draw()
{
	glDeleteVertexArrays(4, VAO);
}

void Draw::update()
{
	vertexCount[0] = drawBackgroundImage(VAO[0]);
	vertexCount[1] = drawOverlay(VAO[1]);
	vertexCount[2] = drawPaddle(VAO[2]);
	vertexCount[3] = drawBall(VAO[3]);
}


int Draw::drawBackgroundImage(GLuint VAO)
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

int Draw::drawOverlay(GLuint VAO)
{
	// create the vertices and the indices

	float osTB = 1 - (36.0f / (height / 2)); // offsetTopBottom
	std::vector<Vertex> vertices{
		// positions         // colors        
	  { 1.0f,  1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // top top right
	  { 1.0f,  osTB, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // top bottom right
	  {-1.0f,  osTB, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // top bottom left
	  {-1.0f,  1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // top top left 

	  { 1.0f, -osTB, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // bottom top right
	  { 1.0f, -1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // bottom bottom right
	  {-1.0f, -1.0f, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }, // bottom bottom left
	  {-1.0f, -osTB, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f }  // bottom top left 
	};

	std::vector<GLuint> indices{
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
		4, 5, 7, // third triangle
		5, 6, 7  // fourth triangle
	};

	int numberLines = (height - 36) / 72;
	float offsetLength = 72.0f / height;
	float partLength = (float)(2 - offsetLength * (numberLines - 1 + 2)) / numberLines;
	float partWidth = 36.0f / width;

	float toCo = osTB; // topCord
	for (int i = 0; i < numberLines; i++)
	{
		float boCo = toCo - partLength; // bottomCord
		vertices.push_back({ partWidth, toCo, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f });
		vertices.push_back({ partWidth, boCo, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f });
		vertices.push_back({ -partWidth, boCo, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f });
		vertices.push_back({ -partWidth, toCo, 0.1f,   0.0f, 0.0f, 0.0f, 0.75f });
		toCo = boCo - offsetLength;

		indices.push_back(8 + 4 * i + 0);
		indices.push_back(8 + 4 * i + 1);
		indices.push_back(8 + 4 * i + 3);
		indices.push_back(8 + 4 * i + 1);
		indices.push_back(8 + 4 * i + 2);
		indices.push_back(8 + 4 * i + 3);
	}

	GLuint VBO, EBO;
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float) * 7, vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

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

	return (int)indices.size();
}

int Draw::drawPaddle(GLuint VAO)
{
	// create the vertices and the indices
	float xDim = 72.0f / width;
	float yDim = 144.0f / height;
	float vertices[] = {
		// positions										 // colors
		 1 - 18.0f / width,			 yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // top right
		 1 - 18.0f / width,			-yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // bottom right
		 1 - 18.0f / width - xDim,	-yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		 1 - 18.0f / width - xDim,   yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // top left

		 // positions										 // colors
		 18.0f / width + xDim - 1,   yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // top right
		 18.0f / width + xDim - 1,	-yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // bottom right
		 18.0f / width - 1,			-yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		 18.0f / width - 1,			 yDim + rightPaddleY, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle

		4, 5, 7, // third triangle
		5, 6, 7  // fourth trinagle
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

int Draw::drawBall(GLuint VAO)
{
	// create the vertices and the indices
	float xDim = 36.0f / width;
	float yDim = 36.0f / height;
	float vertices[] = {
		// positions								   // colors
		  xDim,	 yDim, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // top right
		  xDim,	-yDim, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // bottom right
		 -xDim,	-yDim, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // bottom left
		 -xDim,  yDim, 0.2f,   0.0f, 0.0f, 0.0f, 1.0f, // top left
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3, // second triangle
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
