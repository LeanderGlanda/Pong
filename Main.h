#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>

#include <iostream>
#include <vector>
#include <thread>

#include "Draw.h"

#define CHECK_ERROR() \
{\
	GLenum err = glGetError(); \
	if (err != GL_NO_ERROR) \
	{\
		printf("glGetError returns %d\n", err); \
	}\
}

GLuint createShader(const char* vertexFilename, const char* fragmentFilename);
void updateRightPaddle(Draw& draw, GLFWwindow* window);
void updateBall(Draw& draw);

extern int height;
extern int width;