#ifndef RESOURCE_H
#define RESOURCE_H

#include "../shader.h"
#include "../Texture/texture.h"

#include <map>
#include <string>

class Resource
{
private:
	std::unordered_map<std::string, Shader> shaders;
	std::unordered_map<std::string, Texture> textures;

public:
	void loadShader(const char* vFile, const char* fFile, const std::string& name);
	Shader& getShader(const std::string& name);

	void loadTexture(const char* filePath, const std::string& name);
	Texture& getTexture(const std::string& name);

	void clear();
};

#endif
