#include "Main.h"

int width = 1280;
int height = 720;

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height);

void printFPS() {
	static std::chrono::time_point<std::chrono::steady_clock> oldTime = std::chrono::high_resolution_clock::now();
	static int fps; fps++;

	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::seconds{ 1 }) {
		oldTime = std::chrono::high_resolution_clock::now();
		std::cout << "FPS: " << fps << "\n";
		fps = 0;
	}
}

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
	Draw draw;
	draw.update();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	CHECK_ERROR();

	GLuint backgroundShader = createShader("vertexShader.glsl", "fragmentShader.glsl");


	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	using namespace std::chrono_literals;
	// Render-Loop
	while (!glfwWindowShouldClose(window))
	{
		updateRightPaddle(draw, window);
		updateBall(draw);

		draw.update();

		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(backgroundShader);
		for (int i = 0; i < 4; i++)
		{
			glBindVertexArray(draw.VAO[i]);
			glDrawElements(GL_TRIANGLES, draw.vertexCount[i], GL_UNSIGNED_INT, 0);
		}

		/*if (draw.ball.centerX >= 0.85)
			std::this_thread::sleep_for(1000ms);
		else*/
			std::this_thread::sleep_for(10ms);
			 
		printFPS();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Clean up
	glDeleteProgram(backgroundShader);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	glfwTerminate();
}

void framebuffer_size_callback(GLFWwindow* window, int _width, int _height)
{
	glViewport(0, 0, _width, _height);
	width = _width;
	height = _height;
}