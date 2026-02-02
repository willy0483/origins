#include "camera.h"

Camera::Camera(int newWidth, int newHeight, glm::vec3 newPosition)
	: position(newPosition)
	, width(newWidth)
	, height(newHeight)
{}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + orientation, up);
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	camMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(camMatrix));
}

void Camera::Inputs(GLFWwindow* window, float deltaTime)
{
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position += speed * deltaTime * orientation;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position += speed * deltaTime * -glm::normalize(glm::cross(orientation, up));
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position += speed * deltaTime * -orientation;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += speed * deltaTime * glm::normalize(glm::cross(orientation, up));
	}
}
