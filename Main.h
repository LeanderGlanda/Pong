#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>

#include <iostream>
#include <vector>
#include <thread>

#define CHECK_ERROR() \
{\
	GLenum err = glGetError(); \
	if (err != GL_NO_ERROR) \
	{\
		printf("glGetError returns %d\n", err); \
	}\
}

GLuint createShader(const char* vertexFilename, const char* fragmentFilename);

extern int height;
extern int width;