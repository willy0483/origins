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

	std::vector<float> plane;
	std::vector<unsigned int> indices;

	int div = 6;
	float triangleSide = 2.0f / div;
	float start = -(div * triangleSide) * 0.5f;
	for(int row = 0; row < div + 1; row++)
	{
		for(int col = 0; col < div + 1; col++)
		{
			glm::vec3 currentVec = glm::vec3(start + col * triangleSide, 0.0, start + row * -triangleSide);
			plane.push_back(currentVec.x);
			plane.push_back(currentVec.y);
			plane.push_back(currentVec.z);
		}
	}

	for(int row = 0; row < div; row++)
	{
		for(int col = 0; col < div; col++)
		{
			int index = row * (div + 1) + col;
			// top triangle
			indices.push_back(index);
			indices.push_back(index + (div + 1) + 1);
			indices.push_back(index + (div + 1));

			// bottom triangle
			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + (div + 1) + 1);
		}
	}

	std::cout << "Plane: " << plane.size() << std::endl;
	std::cout << "Indices: " << indices.size() << std::endl;

	unsigned int VAO;
	unsigned int VBO;

	// generate
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind - data
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, plane.size() * sizeof(float), plane.data(), GL_STATIC_DRAW);

	// attributes
	// positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// unbind
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// main loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, -1.5f, -2.0f));
		view = glm::rotate(view, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		proj = glm::perspective(glm::radians(45.0f), ((float)width / height), 0.1f, 100.0f);

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, indices.data());

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
