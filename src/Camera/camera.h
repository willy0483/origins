#ifndef CAMERA_H
#define CAMERA_H

#include "../shader.h"
#include "../Config/config.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 direction;

	glm::mat4 cameraMatrix;

	int width;
	int height;

	float speed = 200.0f;

public:
	Camera(int width, int height, const glm::vec3& position);

	void UpdateMatrix(float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);

	void Input(GLFWwindow* window, float deltaTime);
};

#endif
