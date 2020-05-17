#pragma once
#include <engine/game_object.hpp>
#include <engine/texture.hpp>

enum BreakoutPowerUp {
	/*
	Speed: increases the velocity of the ball by 20%.
	Sticky : when the ball collides with the paddle, the ball remains stuck to the paddle unless the spacebar is pressed again.This allows the player to better position the ball before releasing it.
	Pass - Through : collision resolution is disabled for non - solid blocks, allowing the ball to pass through multiple blocks.
	Pad - Size - Increase : increases the width of the paddle by 50 pixels.
	Confuse : activates the confuse postprocessing effect for a short period of time, confusing the user.
	Chaos : activates the chaos postprocessing effect for a short period of time, heavily disorienting the user.
	*/

	Speed = 0,
	Sticky,
	Pass,
	Pad,
	Confuse,
	Chaos
};

// PowerUp inherits its state and rendering functions from
// GameObject but also holds extra information to state its
// active duration and whether it is activated or not. 
// The type of PowerUp is stored as a BreakoutPowerup.
class PowerUp : public GameObject {
public:
	BreakoutPowerUp Type;
	float Duration;
	bool Activated;

	PowerUp(const BreakoutPowerUp& type, glm::vec3 color, float duration, glm::vec2 position, const Texture2D& texture);
};