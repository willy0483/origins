#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include "camera.h"

const unsigned int width = 800;
const unsigned int height = 600;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow*, int width, int height);

int main()
{
	// initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Origins", NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// create shaders
	Shader shader = Shader("src/Shaders/default.vert", "src/Shaders/default.frag");

	// camera - Look around : https://learnopengl.com/Getting-started/Camera


	float vertices[] = {
		-0.5f, -0.5f, 0.5f, // 0: Bottom front left
		-0.5f, -0.5f, -0.5f, // 1: Bottom back left
		0.5f,  -0.5f, -0.5f, // 2: Bottom back right
		0.5f,  -0.5f, 0.5f, // 3: Bottom front right
		-0.5f, 0.5f,  0.5f, // 4: Top front left
		-0.5f, 0.5f,  -0.5f, // 5: Top back left
		0.5f,  0.5f,  -0.5f, // 6: Top back right
		0.5f,  0.5f,  0.5f, // 7: Top front right
	};

	unsigned int indices[] = {
		0, 4, 3, //
		3, 4, 7, //
		1, 2, 6, //
		6, 5, 1, //
		0, 1, 5, //
		5, 4, 0, //
		3, 2, 6, //
		6, 7, 3, //
		7, 6, 5, //
		5, 4, 7, //
		0, 1, 2, //
		2, 3, 0, //
	};

	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	// generate
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind - data
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// attributes
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind
	glBindVertexArray(0);

	// Camera
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	lastFrame = glfwGetTime();

	// main loop
	while(!glfwWindowShouldClose(window))
	{

		double currentFrame = glfwGetTime();
		deltaTime = float(currentFrame - lastFrame);

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window, deltaTime);
		camera.updateMatrix(45.0f, 0.1f, 100.0f);

		shader.use();
		camera.Matrix(shader, "camMatrix");

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastFrame = currentFrame;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	// delete shaders
	shader.deleteProgram();

	// clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}
