#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../time.h"
#include "../Camera/camera.h"
#include "../Resource/resource.h"

#include "../Mesh/mesh.h"

#include "../Config/config.h"

namespace origins
{
	class Game
	{
	private:
		GLFWwindow* window;
		Camera camera;

		double lastTime = 0.0;
		double nowTime = 0.0;
		double deltaTime = 0.0;

		Resource resource;

		std::unique_ptr<Mesh> mesh;

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

} // namespace origins

#endif
