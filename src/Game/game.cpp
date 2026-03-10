#include "game.h"

using namespace origins;

float vertices[] = {
	0.5f,  0.5f,  1.0f, 0.0f, 0.0f, // top right
	0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // bottom left
	-0.5f, 0.5f,  0.0f, 0.0f, 0.0f, // top left
};
unsigned int indices[] = {
	0, 1, 3, // first Triangle
	1, 2, 3 // second Triangle
};

Game::Game()
	: window(nullptr)
{}

int Game::Init()
{
	// initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(config::width, config::height, config::title.c_str(), NULL, NULL);
	if(window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1);

	// glad: load all OpenGL function pointers
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	return 0;
}

void Game::Run()
{
	if(Init() < 0)
	{
		std::cout << "Failed to initialize Game\n" << std::endl;
		return;
	}

	shaderCube = std::make_unique<Shader>("src/Shaders/default.vert", "src/Shaders/default.frag");

	glGenVertexArrays(1, &cube.VAO);
	glGenBuffers(1, &cube.VBO);
	glGenBuffers(1, &cube.EBO);

	glBindVertexArray(cube.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, cube.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	time.lastTime = glfwGetTime();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// main loop
	while(!glfwWindowShouldClose(window))
	{
		time.nowTime = glfwGetTime();
		time.deltaTime = time.nowTime - time.lastTime;

		processInput(window);

		Update();
		Render();

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		time.lastTime = time.nowTime;
	}

	glDeleteVertexArrays(1, &cube.VAO);
	glDeleteBuffers(1, &cube.VBO);
	glDeleteBuffers(1, &cube.EBO);

	glfwTerminate();
}

void Game::Update()
{}

void Game::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	shaderCube->use();

	glBindVertexArray(cube.VAO);
	glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0);
}

namespace origins
{
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

} // namespace origins
