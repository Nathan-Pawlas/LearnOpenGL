#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <iostream>
#include <stdio.h>

bool wireFrame = false;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	// ----------- INITIALIZATION AND WINDOW -----------------
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


	// ------------- SHADER PROGRAMS ------------
	Shader ourShader("Shaders/shader.vert", "Shaders/shader.frag");

	// ----------- VERTEX & ELEMENT BUFFER, VERTEX ARRAY ----------------
	//MESH DATA
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int VBO, EBO, VAO;
	glGenVertexArrays(1, &VAO); //CREATE A VERTEX ARRAY OBJECT
	glGenBuffers(1, &VBO); //CREATE A VERTEX BUFFER OBJECT

	glBindVertexArray(VAO); //BIND VERTEX ARRAY (BEFORE BINDING VERT BUFFER!)

	//BIND VBO INTO MEMORY
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //SPECIFY OBJECT TYPE (Vertex Buffer)
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //COPY VERTEX DATA TO VBO

	//possition attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //SPECIFY TO OPENGL HOW TO INTERPRET VERTEX DATA
	glEnableVertexAttribArray(0);
	//color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0); //WE CAN UNBIND THE VBO B/C THE VBO IS REGISTERED WITH THE VAO NOW
	glBindVertexArray(0); //UNBIND THE VAO SO OTHER VAO CALLS WON'T EFFECT IT (We'll rebind it when drawing)


	


	// --------- RENDER LOOP --------------
	while (!glfwWindowShouldClose(window))
	{
		//INPUT
		processInput(window);

		//RENDERING
		glClearColor(0.5f, 0.8f, 1.0f, 1.0f); //SET WINDOW COLOR
		glClear(GL_COLOR_BUFFER_BIT);

		//DRAW
		ourShader.use();
		glBindVertexArray(VAO); //BIND VAO (HAS PTR TO VBO DATA IN IT)
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//POLL EVENTS, SWAP BUFFERS
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	//TERMINATE
	glfwTerminate();
	return 0;
}

float delay = 10;
void processInput(GLFWwindow* window)
{
	delay--;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && delay < 0)
	{
		wireFrame = !wireFrame;
		delay = 10;
	}

	if (wireFrame)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//UPDATES VIEWPORT TO MATCH WINDOW SIZE
	glViewport(0, 0, width, height);
}