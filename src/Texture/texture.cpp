#include "texture.h"

using namespace std;

Texture::Texture(const string& path)
	: path(path)
{}

Texture::~Texture()
{
	glDeleteTextures(1, &id);
}

void Texture::LoadTexture(Shader& shader, const string& uniform, int index)
{
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
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

	shader.use();
	glUniform1i(glGetUniformLocation(shader.ID, uniform.c_str()), index);
}

void Texture::Bind(unsigned int uni) const
{
	glActiveTexture(GL_TEXTURE0 + uni);
	glBindTexture(GL_TEXTURE_2D, GetId());
}

int Texture::GetId() const
{
	return id;
}
