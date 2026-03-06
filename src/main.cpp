#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/noise.hpp>

#include "shader.h"
#include "Camera/camera.h"

const unsigned int width = 800;
const unsigned int height = 600;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// camera
Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));

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

	Shader defaultShader = Shader("src/Shaders/default.vert", "src/Shaders/default.frag");
	Shader lightShader = Shader("src/Shaders/light.vert", "src/Shaders/light.frag");

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

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	unsigned int lightVAO;
	unsigned int lightVBO;
	unsigned int lightEBO;

	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glGenBuffers(1, &lightEBO);

	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, lightEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

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

		camera.Input(window, deltaTime);
		camera.UpdateMatrix(45.0f, 0.1f, 100.0f);

		glm::mat4 model = glm::mat4(1.0f);

		float time = glfwGetTime();
		model = glm::rotate(model, time * 0.7f, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, time * 1.1f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, time * 0.4f, glm::vec3(0.0f, 0.0f, 1.0f));

		defaultShader.use();
		camera.Matrix(defaultShader, "cameraMatrix");
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		lightShader.use();
		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, glm::vec3(2.0f, 2.0f, 0.0f));
		camera.Matrix(lightShader, "cameraMatrix");
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

		glBindVertexArray(lightVAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastFrame = currentFrame;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);
	glDeleteBuffers(1, &lightEBO);

	defaultShader.deleteProgram();
	lightShader.deleteProgram();

	// clearing all previously allocated GLFW resources
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}
