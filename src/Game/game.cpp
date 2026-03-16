#include "game.h"

using namespace origins;

std::vector<Vertex> vertices = {
	{ { 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 1.0f } },
	{ { 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } },
	{ { 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f } },
	{ { 0.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f } },
};

std::vector<unsigned int> indices = {
	0, 1, 3, //
	1, 2, 3, //
};

Game::Game()
	: window(nullptr)
	, camera(config::width, config::height, glm::vec3(0.0f, 0.0f, 0.0f))
	, shaderCube(nullptr)
	, mesh(nullptr)
{}

Game::~Game()
{
	mesh.reset();
	shaderCube.reset();
	resources.textures.clear();
	glfwTerminate();
}

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

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

	resources.textures.emplace("wall", std::make_shared<Texture>(config::assets::path::wall.c_str()));
	resources.textures.emplace("face", std::make_shared<Texture>(config::assets::path::face.c_str()));

	resources.textures["wall"]->LoadTexture(*shaderCube, "texture0", 0);
	resources.textures["face"]->LoadTexture(*shaderCube, "texture1", 1);

	mesh = std::make_unique<Mesh>(vertices, indices);

	Sprite sprite;
	sprite.position = glm::vec2(100.0f, 100.0f);
	sprite.size = glm::vec2(64.0f, 64.0f);
	sprite.rotation = 0.0f;
	sprite.texture = resources.textures["face"].get();

	Object object;
	object.sprite = &sprite;

	objects.push_back(object);

	lastTime = glfwGetTime();

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// main loop
	while(!glfwWindowShouldClose(window))
	{
		nowTime = glfwGetTime();
		deltaTime = nowTime - lastTime;

		processInput(window);

		Update();
		Render();

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

		lastTime = nowTime;
	}
}

void Game::Update()
{
	camera.Input(window, deltaTime);
	camera.UpdateMatrix(0.0f, 1.0f);
}

void Game::Render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	camera.Matrix(*shaderCube, "cameraMatrix");

	for(Object& object : objects)
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(object.sprite->position, 0.0f));
		model = glm::rotate(model, glm::radians(object.sprite->rotation), glm::vec3(0, 0, 1));
		model = glm::scale(model, glm::vec3(object.sprite->size, 1.0f));

		shaderCube->use();
		glUniformMatrix4fv(glGetUniformLocation(shaderCube->ID, "model"), 1, GL_FALSE, glm::value_ptr(model));

		object.sprite->texture->Bind(0);

		mesh->Draw(*shaderCube);
	}
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
