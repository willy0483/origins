#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <memory>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader.h"
#include "../time.h"
#include "../mesh.h"

#include "../Config/config.h"

namespace origins
{

	class Game
	{
	private:
		GLFWwindow* window;
		Time time;

		std::unique_ptr<Shader> shaderCube;

		Mesh cube;

	public:
		Game();
		~Game() = default;

		int Init();
		void Run();
		void Update();
		void Render();
	};

	void processInput(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow*, int width, int height);

} // namespace origins

#endif
