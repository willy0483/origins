#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"
#include "../time.h"
#include "../Camera/camera.h"

#include "../Config/config.h"

class Game
{
private:
	GLFWwindow* window;
	Camera camera;
	Time time;

public:
	Game();
	~Game();

	int Init();
	void Run();
	void Update();
	void Render();
};

void processInput(GLFWwindow* window);
void framebuffer_size_callback(GLFWwindow*, int width, int height);

#endif
