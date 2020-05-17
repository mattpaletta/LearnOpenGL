#include "power_up.hpp"

PowerUp::PowerUp(const BreakoutPowerUp& type, glm::vec3 color, float duration, glm::vec2 position, const Texture2D& texture, const glm::vec2 SIZE, const glm::vec2 VELOCITY) : GameObject(position, SIZE, texture, color, VELOCITY), Type(type), Duration(duration), Activated() { }
