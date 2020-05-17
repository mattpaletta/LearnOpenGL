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
	const glm::vec2 PLAYER_SIZE{ 100.0f, 20.f };
	const GLfloat PLAYER_VELOCITY{ 500.0f };

	// Initial velocity of the Ball
	const glm::vec2 INITIAL_BALL_VELOCITY{ 100.0f, -350.0f };

	// Radius of the ball object
	const float BALL_RADIUS { 12.5f };
	BallObject* Ball;
	ParticleGenerator* Particles;
	BreakoutEffects* Effects;

	// Effects Variables
	float ShakeTime = 0.0f;


	std::vector<PowerUp>  PowerUps;

public:
    Breakout(const int width, const int height) : Game(width, height, "Breakout") {}

    void Init() override;
    void Render() override;

	void ResetLevel();
	void ResetPlayer();

	void Update(double dt) override;
	void DoCollisions() override;

	void ProcessInput(double dt) override;

	void SpawnPowerUps(GameObject& block);
	void UpdatePowerUps(float dt);
	void ActivatePowerUp(const PowerUp& powerUp);
};
