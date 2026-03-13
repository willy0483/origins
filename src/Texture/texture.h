#ifndef TEXTURE_H
#define TEXTURE_H

#include "../shader.h"

#include <iostream>
#include <string>

#include <glad/glad.h>
#include <stb_image.h>

class Texture
{
private:
	unsigned int id;

	int width;
	int height;
	int nrChannels;

	std::string path;

public:
	Texture(const std::string& path);
	~Texture();

	void LoadTexture(Shader& shader, const std::string& uniform, int index);

	void Bind(unsigned int uni) const;
	int GetId() const;
};

#endif
