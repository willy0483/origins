#ifndef SPRITE_H
#define SPRITE_H

#include "Texture/texture.h"

#include <glm/glm.hpp>

struct Sprite
{
	glm::vec2 position{ 0.0f, 0.0f };
	glm::vec2 size{ 32.0f, 32.0f };
	float rotation = 0.0f;

	Texture* texture = nullptr;
};

#endif
