#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Camera/camera.h"

const unsigned int width = 800;
const unsigned int height = 600;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// camera
Camera camera(width, height, glm::vec3(0.0f, 0.0f, 3.0f));

// lighting
glm::vec3 lightPos(0.0f, 1.5f, 2.0f);

float speed = 1.0f;
float radius = 2.0f;
float angle = 0.0f;

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
		-0.5f, -0.5f, -0.5f, 0.0f,	0.0f,  -1.0f, //
		0.5f,  -0.5f, -0.5f, 0.0f,	0.0f,  -1.0f, //
		0.5f,  0.5f,  -0.5f, 0.0f,	0.0f,  -1.0f, //
		0.5f,  0.5f,  -0.5f, 0.0f,	0.0f,  -1.0f, //
		-0.5f, 0.5f,  -0.5f, 0.0f,	0.0f,  -1.0f, //
		-0.5f, -0.5f, -0.5f, 0.0f,	0.0f,  -1.0f, //

		-0.5f, -0.5f, 0.5f,	 0.0f,	0.0f,  1.0f, //
		0.5f,  -0.5f, 0.5f,	 0.0f,	0.0f,  1.0f, //
		0.5f,  0.5f,  0.5f,	 0.0f,	0.0f,  1.0f, //
		0.5f,  0.5f,  0.5f,	 0.0f,	0.0f,  1.0f, //
		-0.5f, 0.5f,  0.5f,	 0.0f,	0.0f,  1.0f, //
		-0.5f, -0.5f, 0.5f,	 0.0f,	0.0f,  1.0f, //

		-0.5f, 0.5f,  0.5f,	 -1.0f, 0.0f,  0.0f, //
		-0.5f, 0.5f,  -0.5f, -1.0f, 0.0f,  0.0f, //
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f,  0.0f, //
		-0.5f, -0.5f, 0.5f,	 -1.0f, 0.0f,  0.0f, //
		-0.5f, 0.5f,  0.5f,	 -1.0f, 0.0f,  0.0f, //

		0.5f,  0.5f,  0.5f,	 1.0f,	0.0f,  0.0f, //
		0.5f,  0.5f,  -0.5f, 1.0f,	0.0f,  0.0f, //
		0.5f,  -0.5f, -0.5f, 1.0f,	0.0f,  0.0f, //
		0.5f,  -0.5f, -0.5f, 1.0f,	0.0f,  0.0f, //
		0.5f,  -0.5f, 0.5f,	 1.0f,	0.0f,  0.0f, //
		0.5f,  0.5f,  0.5f,	 1.0f,	0.0f,  0.0f, //

		-0.5f, -0.5f, -0.5f, 0.0f,	-1.0f, 0.0f, //
		0.5f,  -0.5f, -0.5f, 0.0f,	-1.0f, 0.0f, //
		0.5f,  -0.5f, 0.5f,	 0.0f,	-1.0f, 0.0f, //
		0.5f,  -0.5f, 0.5f,	 0.0f,	-1.0f, 0.0f, //
		-0.5f, -0.5f, 0.5f,	 0.0f,	-1.0f, 0.0f, //
		-0.5f, -0.5f, -0.5f, 0.0f,	-1.0f, 0.0f, //

		-0.5f, 0.5f,  -0.5f, 0.0f,	1.0f,  0.0f, //
		0.5f,  0.5f,  -0.5f, 0.0f,	1.0f,  0.0f, //
		0.5f,  0.5f,  0.5f,	 0.0f,	1.0f,  0.0f, //
		0.5f,  0.5f,  0.5f,	 0.0f,	1.0f,  0.0f, //
		-0.5f, 0.5f,  0.5f,	 0.0f,	1.0f,  0.0f, //
		-0.5f, 0.5f,  -0.5f, 0.0f,	1.0f,  0.0f, //
	};

	unsigned int VAO;
	unsigned int VBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	unsigned int lightVAO;
	unsigned int lightVBO;

	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);

	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	defaultShader.use();
	glUniform3fv(glGetUniformLocation(defaultShader.ID, "material.ambient"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
	glUniform3fv(glGetUniformLocation(defaultShader.ID, "material.diffuse"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
	glUniform3fv(glGetUniformLocation(defaultShader.ID, "material.specular"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	glUniform1f(glGetUniformLocation(defaultShader.ID, "material.shininess"), 32.0f);

	glUniform3fv(glGetUniformLocation(defaultShader.ID, "light.ambient"), 1, glm::value_ptr(glm::vec3(0.2f, 0.2f, 0.2f)));
	glUniform3fv(glGetUniformLocation(defaultShader.ID, "light.diffuse"), 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
	glUniform3fv(glGetUniformLocation(defaultShader.ID, "light.specular"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

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

		defaultShader.use();
		glUniform3fv(glGetUniformLocation(defaultShader.ID, "objectColor"), 1, glm::value_ptr(glm::vec3(1.0f, 0.5f, 0.31f)));
		glUniform3fv(glGetUniformLocation(defaultShader.ID, "lightColor"), 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform3fv(glGetUniformLocation(defaultShader.ID, "lightPos"), 1, glm::value_ptr(lightPos));
		glUniform3fv(glGetUniformLocation(defaultShader.ID, "viewPos"), 1, glm::value_ptr(camera.GetPosition()));

		glm::mat4 model = glm::mat4(1.0f);

		/* float time = glfwGetTime();
		model = glm::rotate(model, time * 0.7f, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, time * 1.1f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, time * 0.4f, glm::vec3(0.0f, 0.0f, 1.0f));
        */

		defaultShader.use();
		camera.Matrix(defaultShader, "cameraMatrix");
		glUniformMatrix4fv(glGetUniformLocation(defaultShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		lightShader.use();
		lightPos.x = std::cos(angle) * radius;
		lightPos.z = std::sin(angle) * radius;

		glm::mat4 lightModel = glm::mat4(1.0f);
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		camera.Matrix(lightShader, "cameraMatrix");
		glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		angle += speed * deltaTime;

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastFrame = currentFrame;
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glDeleteVertexArrays(1, &lightVAO);
	glDeleteBuffers(1, &lightVBO);

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
