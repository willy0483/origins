#include "resource.h"

void Resource::loadShader(const char* vFile, const char* fFile, const std::string& name)
{
	Shader shader;
	shader.load(vFile, fFile);
	shaders[name] = shader;
}

Shader& Resource::getShader(const std::string& name)
{
	return shaders[name];
}

void Resource::loadTexture(const char* filePath, const std::string& name)
{
	Texture texture;
	texture.load(filePath);
	textures[name] = texture;
}

Texture& Resource::getTexture(const std::string& name)
{
	return textures[name];
}

void Resource::clear()
{
	for(auto itr : shaders)
	{
		itr.second.deleteProgram();
	}
	for(auto itr : textures)
	{
		itr.second.deleteTexture();
	}
}
