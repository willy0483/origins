#ifndef RESOURCE_H
#define RESOURCE_H

#include "../shader.h"

#include <map>
#include <string>

class Resource
{
private:
	std::unordered_map<std::string, Shader> shaders;

public:
	void loadShader(const char* vFile, const char* fFile, const std::string& name);
	Shader& getShader(const std::string& name);

	void clear();
};

#endif
