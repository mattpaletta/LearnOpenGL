//
//  Breakout.cpp
//  breakout
//
//  Created by Matthew Paletta on 2020-04-28.
//
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <filesystem>
#include <future>

#include "breakout.hpp"

#include "engine/resource.hpp"
#include "engine/engine.hpp"

glm::vec2 Breakout::PLAYER_SIZE() {
	return this->engine->scaleObj(100.0f, 20.0f);
}

float Breakout::BALL_RADIUS() {
	return this->engine->scaleObj( 12.5f );
}

float Breakout::PLAYER_VELOCITY() {
	return this->engine->scaleObj( 500.0f );
}

glm::vec2 Breakout::INITIAL_BALL_VELOCITY() {
	return this->engine->scaleObj(100.0f, -350.0f);
}

void Breakout::Init() {
	// Load sounds
	this->engine->LoadSound(ResourceManager::RegisterSound("../sounds/bleep.wav", "non-solid"));
	this->engine->LoadSound(ResourceManager::RegisterSound("../sounds/solid.wav", "solid"));
	this->engine->LoadSound(ResourceManager::RegisterSound("../sounds/powerup.wav", "powerup"));
	this->engine->LoadSound(ResourceManager::RegisterSound("../sounds/paddle.wav", "paddle"));
	this->engine->LoadSound(ResourceManager::RegisterSound("../sounds/breakout.wav", "music"), true, true);

	// load shaders
	ResourceManager::LoadShader("../src/sprite.vert", "../src/sprite.frag", "", "sprite");
	ResourceManager::LoadShader("../src/particle.vert", "../src/particle.frag", "", "particle");
	ResourceManager::LoadShader("../src/post_processing.vert", "../src/post_processing.frag", "", "postprocessing");

	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);

	ResourceManager::GetShader("sprite").setInt("image", 0, true);
	ResourceManager::GetShader("sprite").setMat4("projection", projection);
	ResourceManager::GetShader("particle").setInt("sprite", 0, true);
	ResourceManager::GetShader("particle").setMat4("projection", projection, false);

	// load textures
	ResourceManager::LoadTexture("../textures/background.jpg", false, "background");
	ResourceManager::LoadTexture("../textures/awesomeface.png", true, "face");
	ResourceManager::LoadTexture("../textures/block.png", false, "block");
	ResourceManager::LoadTexture("../textures/block_solid.png", false, "block_solid");
	ResourceManager::LoadTexture("../textures/paddle.png", true, "paddle");
	ResourceManager::LoadTexture("../textures/particle.png", true, "particle");

	ResourceManager::LoadTexture("../textures/powerup_speed.png", true, "powerup_speed");
	ResourceManager::LoadTexture("../textures/powerup_sticky.png", true, "powerup_sticky");
	ResourceManager::LoadTexture("../textures/powerup_increase.png", true, "powerup_increase");
	ResourceManager::LoadTexture("../textures/powerup_confuse.png", true, "powerup_confuse");
	ResourceManager::LoadTexture("../textures/powerup_chaos.png", true, "powerup_chaos");
	ResourceManager::LoadTexture("../textures/powerup_passthrough.png", true, "powerup_passthrough");

	// Configure Rendering
	this->engine->setSpriteRendering("sprite");

	this->Effects = new BreakoutEffects(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);
	constexpr int num_particles = 500;
	this->Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), num_particles);

	// load levels
	GameLevel one; one.Load("../levels/one.lvl", this->Width, this->Height / 2);
	GameLevel two; two.Load("../levels/two.lvl", this->Width, this->Height / 2);
	GameLevel three; three.Load("../levels/three.lvl", this->Width, this->Height / 2);
	GameLevel four; four.Load("../levels/four.lvl", this->Width, this->Height / 2);

	this->Levels.push_back(one);
	this->Levels.push_back(two);
	this->Levels.push_back(three);
	this->Levels.push_back(four);
	this->Level = 0;

	const glm::vec2 playerPos{
		this->Width / 2.0f - this->PLAYER_SIZE().x / 2.0f,
		this->Height - this->PLAYER_SIZE().y };
	this->Player = new GameObject(playerPos, this->PLAYER_SIZE(), ResourceManager::GetTexture("paddle"));

	const glm::vec2 ballPos = playerPos + glm::vec2(this->PLAYER_SIZE().x / 2.0f - this->BALL_RADIUS(), -this->BALL_RADIUS() * 2.0f);
	this->Ball = new BallObject(ballPos, this->BALL_RADIUS(), this->INITIAL_BALL_VELOCITY(), ResourceManager::GetTexture("face"));

	// Start Music
	this->engine->Play(ResourceManager::GetSound("music"));
}

void Breakout::ResetLevel() {
	if (this->Level == 0)
		this->Levels[0].Load("../levels/one.lvl", this->Width, this->Height / 2);
	else if (this->Level == 1)
		this->Levels[1].Load("../levels/two.lvl", this->Width, this->Height / 2);
	else if (this->Level == 2)
		this->Levels[2].Load("../levels/three.lvl", this->Width, this->Height / 2);
	else if (this->Level == 3)
		this->Levels[3].Load("../levels/four.lvl", this->Width, this->Height / 2);
}

void Breakout::ResetPlayer() {
	// reset player/ball stats
	Player->Size = PLAYER_SIZE();
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE().x / 2.0f, this->Height - PLAYER_SIZE().y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE().x / 2.0f - BALL_RADIUS(), -(BALL_RADIUS() * 2.0f)), INITIAL_BALL_VELOCITY());

	// also disable all active powerups
	Effects->Chaos = Effects->Confuse = false;
	Ball->PassThrough = Ball->Sticky = false;
	Player->Color = glm::vec3(1.0f);
	Ball->Color = glm::vec3(1.0f);
}

void Breakout::Update(double dt) {
	// Update objects
	this->Ball->Move(dt, this->Width);

	// Check for collisions
	this->DoCollisions();

	// update particles
	this->Particles->Update(dt, *this->Ball, 2, glm::vec2(this->Ball->Radius / 2.0f));

	// Update powerups
	this->UpdatePowerUps(dt);

	// Reduce shake time
	if (this->ShakeTime > 0.0f) {
		this->ShakeTime -= dt;
		if (this->ShakeTime <= 0.0f) {
			this->Effects->Shake = false;
		}
	}

	if (Ball->Position.y >= this->Height) { // did ball reach bottom edge?
		this->ResetLevel();
		this->ResetPlayer();
	}
}

void Breakout::Render() {
	if (this->State == GAME_ACTIVE) {

		// Begin rendering to postprocessing framebuffer
		Effects->RenderBlock(glfwGetTime(), [this] {
			// draw background
			this->engine->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->Width, this->Height), 0.0f);
			auto renderer = this->engine->getRenderer();
			// draw level
			this->Levels[this->Level].Draw(*renderer);

			// draw paddle
			this->Player->Draw(*renderer);

			// draw PowerUps
			for (const PowerUp& powerUp : this->PowerUps) {
				if (!powerUp.Destroyed) {
					powerUp.Draw(*renderer);
				}
			}

			// draw particles
			this->Particles->Draw();

			// draw ball last
			this->Ball->Draw(*renderer);
		});
	}
}

enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};

Direction VectorDirection(glm::vec2 target) {
	glm::vec2 compass[] = {
		glm::vec2(0.0f, 1.0f),	// up
		glm::vec2(1.0f, 0.0f),	// right
		glm::vec2(0.0f, -1.0f),	// down
		glm::vec2(-1.0f, 0.0f)	// left
	};
	float max = 0.0f;
	unsigned int best_match = -1;
	for (unsigned int i = 0; i < 4; i++) {
		float dot_product = glm::dot(glm::normalize(target), compass[i]);
		if (dot_product > max) {
			max = dot_product;
			best_match = i;
		}
	}
	return (Direction) best_match;
}

typedef std::tuple<bool, Direction, glm::vec2> Collision;


Collision CheckCollision(BallObject& one, GameObject& two) {// AABB - AABB collision
	// get center point circle first
	glm::vec2 center(one.Position + one.Radius);
	// calculate AABB info (center, half-extents)
	glm::vec2 aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
	glm::vec2 aabb_center(
		two.Position.x + aabb_half_extents.x,
		two.Position.y + aabb_half_extents.y
	);
	// get difference vector between both centers
	glm::vec2 difference = center - aabb_center;
	glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
	// add clamped value to AABB_center and we get the value of box closest to circle
	glm::vec2 closest = aabb_center + clamped;
	// retrieve vector between center circle and closest point AABB and check if length <= radius
	difference = closest - center;

	if (glm::length(difference) <= one.Radius)
		return std::make_tuple(true, VectorDirection(difference), difference);
	else
		return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}

// TODO: Move to the engine.
bool CheckCollision(GameObject& one, GameObject& two) { // AABB - AABB collision
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;

	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;

	// Collision only if on both axes
	return collisionX && collisionY;
}

void Breakout::ActivatePowerUp(const PowerUp& powerUp) {
	switch (powerUp.Type) {
	case BreakoutPowerUp::Speed:
		this->Ball->Velocity *= 1.2;
		break;
	case BreakoutPowerUp::Sticky:
		this->Ball->Sticky = true;
		this->Player->Color = glm::vec3(1.0f, 0.5f, 1.0f);
		break;
	case BreakoutPowerUp::Pass:
		Ball->PassThrough = true;
		Ball->Color = glm::vec3(1.0f, 0.5f, 0.5f);
		break;
	case BreakoutPowerUp::Pad:
		Player->Size.x += 50;
		break;
	case BreakoutPowerUp::Confuse:
		if (!Effects->Chaos) {
			Effects->Confuse = true; // only activate if confuse wasn't already active
		}
		break;
	case BreakoutPowerUp::Chaos:
		if (!Effects->Confuse) {
			Effects->Chaos = true;
		}
		break;
	}
}

bool isOtherPowerUpActive(const std::vector<PowerUp>& powerUps, const BreakoutPowerUp& type) {
	for (const PowerUp& powerUp : powerUps) {
		if (powerUp.Activated) {
			if (powerUp.Type == type) {
				return true;
			}
		}
	}
	return false;
}

void Breakout::UpdatePowerUps(float dt) {
	for (PowerUp& powerUp : this->PowerUps) {
		powerUp.Position += powerUp.Velocity * dt;
		if (powerUp.Activated) {
			powerUp.Duration -= dt;

			if (powerUp.Duration <= 0.0f) {
				// remove powerup from list (will later be removed)
				powerUp.Activated = false;

				// deactivate effects
				const bool otherPowerUpActive = isOtherPowerUpActive(this->PowerUps, powerUp.Type);
				if (!otherPowerUpActive) {	// only reset if no other PowerUp of type is active
					switch (powerUp.Type) {
					case BreakoutPowerUp::Sticky:
						Ball->Sticky = false;
						Player->Color = glm::vec3(1.0f);
						break;
					case BreakoutPowerUp::Pass:
						Ball->PassThrough = false;
						Ball->Color = glm::vec3(1.0f);
						break;
					case BreakoutPowerUp::Confuse:
						Effects->Confuse = false;
						break;
					case BreakoutPowerUp::Chaos:
						Effects->Chaos = false;
						break;
					}
				}
			}
		}
	}
	this->PowerUps.erase(
		std::remove_if(this->PowerUps.begin(), this->PowerUps.end(),
			[](const PowerUp& powerUp) {
				return powerUp.Destroyed && !powerUp.Activated;
			}), this->PowerUps.end());
}

void Breakout::DoCollisions() {
	for (GameObject& box : this->Levels[this->Level].Bricks) {
		if (!box.Destroyed) {
			Collision collision{ CheckCollision(*Ball, box) };
			if (std::get<0>(collision)) {
				if (!box.IsSolid) {
					box.Destroyed = true;
					this->SpawnPowerUps(box);
					this->engine->Play(ResourceManager::GetSound("non-solid"));
				} else {
					// if block is solid, enable shake effect
					this->ShakeTime = 0.05f;
					this->Effects->Shake = true;
					this->engine->Play(ResourceManager::GetSound("solid"));
				}

				// collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
				if (!(Ball->PassThrough && !box.IsSolid)) {
					if (dir == LEFT || dir == RIGHT) { // horizontal collision
						Ball->Velocity.x = -Ball->Velocity.x; // reverse horizontal velocity
						// relocate
						float penetration = Ball->Radius - std::abs(diff_vector.x);
						if (dir == LEFT) {
							Ball->Position.x += penetration; // move ball to right
						} else {
							Ball->Position.x -= penetration; // move ball to left;
						}
					} else { // vertical collision
						Ball->Velocity.y = -Ball->Velocity.y; // reverse vertical velocity
						// relocate
						float penetration = Ball->Radius - std::abs(diff_vector.y);
						if (dir == UP) {
							Ball->Position.y -= penetration; // move ball back up
						} else {
							Ball->Position.y += penetration; // move ball back down
						}
					}

				}
			}

			// See possible bugs: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
		}
	}

	for (PowerUp& powerUp : this->PowerUps) {
		if (!powerUp.Destroyed) {
			if (powerUp.Position.y >= this->Height) {
				powerUp.Destroyed = true;
			}
			if (CheckCollision(*Player, powerUp)) {
				// Collided with player, now activate powerup
				this->ActivatePowerUp(powerUp);
				powerUp.Destroyed = true;
				powerUp.Activated = true;
				this->engine->Play(ResourceManager::GetSound("powerup"));
			}
		}
	}

	Collision result = CheckCollision(*Ball, *Player);
	if (!Ball->Stuck && std::get<0>(result)) {
		// check where it hit the board, and change velocity based on where it hit the board
		float centerBoard = Player->Position.x + Player->Size.x / 2.0f;
		float distance = (Ball->Position.x + Ball->Radius) - centerBoard;
		float percentage = distance / (Player->Size.x / 2.0f);

		// then move accordingly
		float strength = 2.0f;
		glm::vec2 oldVelocity = Ball->Velocity;
		Ball->Velocity.x = INITIAL_BALL_VELOCITY().x * percentage * strength;

		// We always know we have a collision on the top of the paddle
		//Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);

		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);

		// if Sticky powerup is activated, also stick ball to paddle once new velocity vectors were calculated
		Ball->Stuck = Ball->Sticky;

		this->engine->Play(ResourceManager::GetSound("paddle"));
	}
}

void Breakout::ProcessInput(double dt) {
	if (this->State == GAME_ACTIVE) {
		double velocity = PLAYER_VELOCITY() * dt;

		// move player paddle
		if (this->Keys[GLFW_KEY_A]) {
			if (Player->Position.x >= 0.0f) {
				Player->Position.x -= (float) velocity;
				if (Ball->Stuck) {
					Ball->Position.x -= velocity;
				}
			}
		}
		if (this->Keys[GLFW_KEY_D]) {
			if (Player->Position.x <= this->Width - Player->Size.x) {
				Player->Position.x += (float) velocity;
				if (Ball->Stuck) {
					Ball->Position.x += velocity;
				}
			}
		}

		if (this->Keys[GLFW_KEY_SPACE]) {
			Ball->Stuck = false;
		}
	}
}

bool ShouldSpawn(const unsigned int& chance) {
	unsigned int random = rand() % chance;
	return random == 0;
}

void Breakout::SpawnPowerUps(GameObject& block) {
	const auto powerup_size = this->engine->scaleObj(DEFAULT_POWERUP_SIZE.x, DEFAULT_POWERUP_SIZE.y);
	const auto powerup_velocity = this->engine->scaleObj(DEFAULT_VELOCITY.x, DEFAULT_VELOCITY.y);
	if (ShouldSpawn(75)) {// 1 in 75 chance
		this->PowerUps.emplace_back(BreakoutPowerUp::Speed, glm::vec3(0.5f, 0.5f, 1.0f), 0.0f, block.Position, ResourceManager::GetTexture("powerup_speed"), powerup_size, powerup_velocity);
	}
	if (ShouldSpawn(75)) {
		this->PowerUps.emplace_back(BreakoutPowerUp::Sticky, glm::vec3(1.0f, 0.5f, 1.0f), 20.0f, block.Position, ResourceManager::GetTexture("powerup_sticky"), powerup_size, powerup_velocity);
	}
	if (ShouldSpawn(75)) {
		this->PowerUps.emplace_back(BreakoutPowerUp::Pass, glm::vec3(0.5f, 1.0f, 0.5f), 10.0f, block.Position, ResourceManager::GetTexture("powerup_passthrough"), powerup_size, powerup_velocity);
	}
	if (ShouldSpawn(75)) {
		this->PowerUps.emplace_back(BreakoutPowerUp::Pad, glm::vec3(1.0f, 0.6f, 0.4), 0.0f, block.Position, ResourceManager::GetTexture("powerup_increase"), powerup_size, powerup_velocity);
	}

	if (ShouldSpawn(15)) {// negative powerups should spawn more often
		this->PowerUps.emplace_back(BreakoutPowerUp::Confuse, glm::vec3(1.0f, 0.3f, 0.3f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_confuse"), powerup_size, powerup_velocity);
	}
	if (ShouldSpawn(15)) {
		this->PowerUps.emplace_back(BreakoutPowerUp::Chaos, glm::vec3(0.9f, 0.25f, 0.25f), 15.0f, block.Position, ResourceManager::GetTexture("powerup_chaos"), powerup_size, powerup_velocity);
	}
}
