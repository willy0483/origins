#include "texture.h"

using namespace std;

Texture::Texture()
{
	glGenTextures(1, &id);
}

Texture::~Texture()
{}

void Texture::load(const char* filePath)
{
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);
	if(data)
	{
		GLenum format = GL_RGB;
		if(nrChannels == 1)
		{
			format = GL_RED;
		}
		else if(nrChannels == 3)
		{
			format = GL_RGB;
		}
		else if(nrChannels == 4)
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind(unsigned int uni) const
{
	glActiveTexture(GL_TEXTURE0 + uni);
	glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::deleteTexture()
{
	glDeleteTextures(1, &id);
}
