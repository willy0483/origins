#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <vector>
#include <memory>

#include "../Texture/texture.h"

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 texCoords;
};

class Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void SetupMesh();

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<std::shared_ptr<Texture>> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
	~Mesh();

	void Draw(Shader& shader);
};

#endif
