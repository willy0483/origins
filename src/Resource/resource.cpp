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

void Resource::clear()
{
	for(auto itr : shaders)
	{
		itr.second.deleteProgram();
	}
}
