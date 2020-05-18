//
//  Breakout.hpp
//  breakout
//
//  Created by Matthew Paletta on 2020-04-28.
//

#pragma once
#include <iostream>

#include <engine/game.hpp>
#include <engine/particle_generator.hpp>

#include "breakout_effects.hpp"
#include "power_up.hpp"
#include "ball_object.hpp"

class Breakout;

class Breakout : public Game {
private:
	glm::vec2 PLAYER_SIZE();
	float PLAYER_VELOCITY();

	// Initial velocity of the Ball
	glm::vec2 INITIAL_BALL_VELOCITY();

	// Radius of the ball object
	float BALL_RADIUS();
	BallObject* Ball;
	ParticleGenerator* Particles;
	BreakoutEffects* Effects;

	// Effects Variables
	float ShakeTime = 0.0f;

	std::vector<PowerUp> PowerUps;

	unsigned int Lives;

public:
    Breakout(const int width, const int height) : Game(width, height, "Breakout") {}

    void Init() override;
    void Render() override;

	void ResetLevel();
	void ResetPlayer();

	void Update(double dt) override;
	void DoCollisions() override;

	void ProcessInput(double dt) override;

	bool IsCompleted();

	void SpawnPowerUps(GameObject& block);
	void UpdatePowerUps(float dt);
	void ActivatePowerUp(const PowerUp& powerUp);
};
