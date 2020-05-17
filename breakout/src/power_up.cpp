#include "power_up.hpp"

// The size of a PowerUp block
const glm::vec2 POWERUP_SIZE{ 60.0f, 20.0f };
// Velocity a PowerUp block has when spawned
const glm::vec2 VELOCITY{ 0.0f, 150.0f };

PowerUp::PowerUp(const BreakoutPowerUp& type, glm::vec3 color, float duration, glm::vec2 position, const Texture2D& texture) : GameObject(position, POWERUP_SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated() { }