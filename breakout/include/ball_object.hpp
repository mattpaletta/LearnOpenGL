#pragma once

#include "engine/game_object.hpp"

class BallObject : public GameObject {
public:
	// ball state	
	float Radius;
	bool Stuck;
	bool Sticky;
	bool PassThrough;

	BallObject();
	BallObject(glm::vec2 pos, float radius, glm::vec2 velocity, Texture2D sprite);

	glm::vec2 Move(double dt, unsigned int window_width);
	void Reset(glm::vec2 position, glm::vec2 velocity);
};
