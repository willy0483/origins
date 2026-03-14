#include "camera.h"

Camera::Camera(int width, int height, const glm::vec3& position)
	: position(position)
	, width(width)
	, height(height)
{}

void Camera::UpdateMatrix(float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);

	view = glm::translate(view, -position);
	glm::mat4 projection = glm::ortho(0.0f, (float)width, (float)height, 0.0f, nearPlane, farPlane);

	cameraMatrix = projection * view;
}
void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Input(GLFWwindow* window, float deltaTime)
{
	if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		position.y -= speed * deltaTime;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position.y += speed * deltaTime;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position.x -= speed * deltaTime;
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position.x += speed * deltaTime;
	}
}
