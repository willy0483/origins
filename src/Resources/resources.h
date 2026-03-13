#ifndef RESOURCES_H
#define RESOURCES_H

#include "../Texture/texture.h"

#include <memory>
#include <unordered_map>

struct Resources
{
	std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
};

#endif
