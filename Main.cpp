#include "Main.h"

int width = 1280;
int height = 720;

bool refreshOverlay = false;
void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);

int main()
{
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	GLFWwindow* window = glfwCreateWindow(width, height, "Pong", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	/*glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, key_callback);*/

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Setup for render

	GLuint VAO[2];
	glGenVertexArrays(2, VAO);

	int vertexCount[2];

	vertexCount[0] = setupBackgroundImage(VAO[0]);
	vertexCount[1] = setupOverlay(VAO[1]);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	CHECK_ERROR();

	GLuint backgroundShader = createShader("vertexShader.glsl", "fragmentShader.glsl");


	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Render-Loop
	while (!glfwWindowShouldClose(window))
	{
		if (refreshOverlay)
		{
			vertexCount[0] = setupBackgroundImage(VAO[0]);
			vertexCount[1] = setupOverlay(VAO[1]);
		}

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(backgroundShader);
		for (int i = 0; i < 2; i++)
		{
			glBindVertexArray(VAO[i]);
			glDrawElements(GL_TRIANGLES, vertexCount[i], GL_UNSIGNED_INT, 0);
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Clean up
	glDeleteVertexArrays(2, VAO);
	glDeleteProgram(backgroundShader);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
	width = _width;
	height = _height;
	refreshOverlay = true;
}