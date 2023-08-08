#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	//Initialize and Configure GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	//CREATE WINDOW OBJECT
	GLFWwindow* window = glfwCreateWindow(1220, 780, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//SET WINDOW AS THE CONTEXT
	glfwMakeContextCurrent(window);

	//SET VIEWPORT SIZE
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//INITIALIZE GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to Initialize GLAD" << std::endl;
		return -1;
	}

	//RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		//INPUT
		processInput(window);

		//RENDERING
		glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//POLL EVENTS, SWAP BUFFERS
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//TERMINATE
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//UPDATES VIEWPORT TO MATCH WINDOW SIZE
	glViewport(0, 0, width, height);
}