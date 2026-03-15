#ifndef SPRITE_H
#define SPRITE_H

#include <glm/glm.hpp>
#include "../Texture/texture.h"

#include <memory>

struct Sprite
{
	glm::vec2 position;
	glm::vec2 size;
	float rotation;

	Texture* texture;
};

#endif
