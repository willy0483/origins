#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>

struct Vertex
{
	glm::vec3 position;
};

class Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	void SetUpMesh();

public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	Mesh(std::vector<Vertex> newVertices, std::vector<unsigned int> newIndices);
	~Mesh();

	void Draw();
};

#endif
