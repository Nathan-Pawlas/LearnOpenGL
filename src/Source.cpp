#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdio.h>

//VERTEX SHADER
const char* vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//FRAGMENT SHADER
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


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
	//CREATE VERTEX SHADER
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); //CREATE THE SHADER
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //ATTACH SHADER SOURCE CODE TO SHADER OBJECT
	glCompileShader(vertexShader);
			//CHECK FOR COMPILE ERRORS
			int success;
			char infoLog[512];
			glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
				return -1;
			}

	//CREATE FRAGMENT SHADER
	unsigned int fragShader;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER); //CREATE THE SHADER
	glShaderSource(fragShader, 1, &fragmentShaderSource, NULL); //ATTACH SHADER SOURCE CODE TO SHADER OBJECT
	glCompileShader(fragShader);
			//CHECK FOR COMPILE ERRORS
			glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
				return -1;
			}

	//CREATE SHADER PROGRAM
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader); //LINK VERTEX SHADER
	glAttachShader(shaderProgram, fragShader); //LINK FRAG SHADER
	glLinkProgram(shaderProgram);
			//CHECK FOR LINK ERRORS
			glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
				std::cout << "ERROR::SHADER::PROGRAM::LINKAGE_FAILED\n" << infoLog << std::endl;
				return -1;
			}
	glDeleteShader(vertexShader); //DELETE VERTEX SHADER
	glDeleteShader(fragShader); // DELETE FRAG SHADER


	// ----------- VERTEX BUFFER & VERTEX ARRAY ----------------
	//VERTEX DATA
	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};
	unsigned int VBO;
	unsigned int VAO;
	glGenBuffers(1, &VBO); //CREATE AN OPENGL VERTEX BUFFER OBJECT
	glGenVertexArrays(1, &VAO); //CREATE A VERTEX ARRAY OBJECT

	glBindVertexArray(VAO); //BIND VERTEX ARRAY (BEFORE BINDING VERT BUFFER!)
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //SPECIFY OBJECT TYPE (Vertex Buffer)

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //COPY VERTEX DATA TO VBO

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); //SPECIFY TO OPENGL HOW TO INTERPRET VERTEX DATA
	glEnableVertexAttribArray(0);

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
		glUseProgram(shaderProgram); //SPECIFY SHADERS TO USE
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