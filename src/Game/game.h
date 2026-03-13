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

#include "../Mesh/mesh.h"
#include "../Resources/resources.h"

#include "../Config/config.h"

namespace origins
{
	class Game
	{
	private:
		GLFWwindow* window;
		Time time;

		std::unique_ptr<Shader> shaderCube;
		std::unique_ptr<Mesh> mesh;

		Resources resources;

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
