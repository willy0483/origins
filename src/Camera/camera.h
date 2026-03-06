#ifndef CAMERA_H
#define CAMERA_H

#include "../shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class Camera
{
private:
	glm::vec3 position;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 direction;

	float yaw = -90.0f;
	float pitch = 0.0f;

	glm::mat4 cameraMatrix;

	float speed = 6.0f;
	float sensitivity = 80.0f;

	int width;
	int height;

public:
	Camera(int width, int height, const glm::vec3& position);

	void UpdateMatrix(float FOVdeg, float nearPlane, float farPlane);
	void Matrix(Shader& shader, const char* uniform);

	void Input(GLFWwindow* window, float deltaTime);
};

#endif
