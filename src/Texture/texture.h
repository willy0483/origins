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

public:
	Texture();
	~Texture();

	void load(const char* filePath);
	void bind(unsigned int uni) const;
	void deleteTexture();
};

#endif
