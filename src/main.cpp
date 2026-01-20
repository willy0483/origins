#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"

const unsigned int width = 800;
const unsigned int height = 600;

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

	float vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //
		0.5f,  -0.5f, -0.5f, 1.0f, 0.0f, //
		0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
		0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
		-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, //

		-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, //
		0.5f,  -0.5f, 0.5f,	 1.0f, 0.0f, //
		0.5f,  0.5f,  0.5f,	 1.0f, 1.0f, //
		0.5f,  0.5f,  0.5f,	 1.0f, 1.0f, //
		-0.5f, 0.5f,  0.5f,	 0.0f, 1.0f, //
		-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, //

		-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, //
		-0.5f, 0.5f,  -0.5f, 1.0f, 1.0f, //
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
		-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, //
		-0.5f, 0.5f,  0.5f,	 1.0f, 0.0f, //

		0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, //
		0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
		0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
		0.5f,  -0.5f, -0.5f, 0.0f, 1.0f, //
		0.5f,  -0.5f, 0.5f,	 0.0f, 0.0f, //
		0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, //

		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //
		0.5f,  -0.5f, -0.5f, 1.0f, 1.0f, //
		0.5f,  -0.5f, 0.5f,	 1.0f, 0.0f, //
		0.5f,  -0.5f, 0.5f,	 1.0f, 0.0f, //
		-0.5f, -0.5f, 0.5f,	 0.0f, 0.0f, //
		-0.5f, -0.5f, -0.5f, 0.0f, 1.0f, //

		-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
		0.5f,  0.5f,  -0.5f, 1.0f, 1.0f, //
		0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, //
		0.5f,  0.5f,  0.5f,	 1.0f, 0.0f, //
		-0.5f, 0.5f,  0.5f,	 0.0f, 0.0f, //
		-0.5f, 0.5f,  -0.5f, 0.0f, 1.0f, //
	};

	unsigned int VAO;
	unsigned int VBO;

	// generate
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind - data
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// attributes
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// texture coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// unbind
	glBindVertexArray(0);

	// texture
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int image_width;
	int image_height;
	int nrChannels;

	unsigned char* data = stbi_load("assets/wall.jpg", &image_width, &image_height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, "tex0"), 0);

	glEnable(GL_DEPTH_TEST);

	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// main loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		float time = glfwGetTime();
		model = glm::rotate(model, time * 0.7f, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, time * 1.1f, glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, time * 0.4f, glm::vec3(0.0f, 0.0f, 1.0f));
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		proj = glm::perspective(glm::radians(45.0f), ((float)width / height), 0.1f, 100.0f);

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

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
