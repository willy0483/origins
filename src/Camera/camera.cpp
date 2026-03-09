#include "camera.h"

Camera::Camera(int width, int height, const glm::vec3& position)
	: position(position)
	, width(width)
	, height(height)
{}

void Camera::UpdateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(position, position + front, up);

	projection = glm::perspective(glm::radians(FOVdeg), ((float)width / height), nearPlane, farPlane);

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
		position += (speed * deltaTime) * front;
	}
	if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		position -= (speed * deltaTime) * front;
	}
	if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		position -= glm::normalize(glm::cross(front, up)) * (speed * deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		position += glm::normalize(glm::cross(front, up)) * (speed * deltaTime);
	}
	if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		position += (speed * deltaTime) * up;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		position -= (speed * deltaTime) * up;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		yaw -= sensitivity * deltaTime;
	}

	if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		yaw += sensitivity * deltaTime;
	}

	if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		pitch += sensitivity * deltaTime;
	}

	if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		pitch -= sensitivity * deltaTime;
	}
	if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		speed = 12.0f;
	}
	else if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		speed = 6.0f;
	}

	if(pitch > 89.0f)
		pitch = 89.0f;
	if(pitch < -89.0f)
		pitch = -89.0f;

	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);
}

glm::vec3 Camera::GetPosition() const
{
	return position;
}
