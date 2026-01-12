#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "mesh.h"

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

	std::vector<Vertex> vertices = {
		Vertex{ glm::vec3{ -0.5f, 0.0f, 0.5f } }, // Bottom front left
		Vertex{ glm::vec3{ -0.5f, 0.0f, -0.5f } }, // Bottom back left
		Vertex{ glm::vec3{ 0.5f, 0.0f, -0.5f } }, // Bottom back right
		Vertex{ glm::vec3{ 0.5f, 0.0f, 0.5f } }, // Bottom front right

		Vertex{ glm::vec3{ -0.5f, 0.5f, 0.5f } }, // Top front left
		Vertex{ glm::vec3{ -0.5f, 0.5f, -0.5f } }, // Top back left
		Vertex{ glm::vec3{ 0.5f, 0.5f, -0.5f } }, // Top back right
		Vertex{ glm::vec3{ 0.5f, 0.5f, 0.5f } }, // Top front right

	};

	std::vector<unsigned int> indices = {
        // faces
        // front
        0,4,3,//
        3,4,7,//
        // back
        1,2,6,//
        6,5,1,//
        // left
        0,1,5,//
        5,4,0,//
        // right
        3,2,6,//
        6,7,3,//
        // top
        7,6,5,// 
        5,4,7,// 
        // bottom
        0,1,2,//
        2,3,0,//
    };


    Mesh test;
    test.vertices = vertices;
    test.indices = indices;

    test.SetUpMesh();

	glEnable(GL_DEPTH_TEST);

	// main loop
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		view = glm::translate(view, glm::vec3(0.0f, -0.5f, -10.0f));
		proj = glm::perspective(glm::radians(45.0f), ((float)width / height), 0.1f, 100.0f);

		shader.use();
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(shader.ID, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

        test.Draw();

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

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
