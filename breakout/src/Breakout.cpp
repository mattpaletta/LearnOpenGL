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

#include "breakout.hpp"

#include "engine/resource.hpp"
#include "engine/engine.hpp"

void Breakout::Init() {
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
		this->Width / 2.0f - this->PLAYER_SIZE.x / 2.0f,
		this->Height - this->PLAYER_SIZE.y };
	this->Player = new GameObject(playerPos, this->PLAYER_SIZE, ResourceManager::GetTexture("paddle"));

	const glm::vec2 ballPos = playerPos + glm::vec2(this->PLAYER_SIZE.x / 2.0f - this->BALL_RADIUS, -this->BALL_RADIUS * 2.0f);
	this->Ball = new BallObject(ballPos, this->BALL_RADIUS, this->INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("face"));
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
	Player->Size = PLAYER_SIZE;
	Player->Position = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	Ball->Reset(Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -(BALL_RADIUS * 2.0f)), INITIAL_BALL_VELOCITY);
}

void Breakout::Update(double dt) {
	// Update objects
	this->Ball->Move(dt, this->Width);

	// Check for collisions
	this->DoCollisions();

	// update particles
	this->Particles->Update(dt, *this->Ball, 2, glm::vec2(this->Ball->Radius / 2.0f));

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
/*
bool CheckCollision(GameObject& one, GameObject& two) { // AABB - AABB collision
	// Collision x-axis?
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// Collision y-axis?
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// Collision only if on both axes
	return collisionX && collisionY;
}*/

void Breakout::DoCollisions() {
	for (GameObject& box : this->Levels[this->Level].Bricks) {
		if (!box.Destroyed) {
			Collision collision{ CheckCollision(*Ball, box) };
			if (std::get<0>(collision)) {
				if (!box.IsSolid) {
					box.Destroyed = true;
				} else {
					// if block is solid, enable shake effect
					this->ShakeTime = 0.05f;
					this->Effects->Shake = true;
				}

				// collision resolution
				Direction dir = std::get<1>(collision);
				glm::vec2 diff_vector = std::get<2>(collision);
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

			// See possible bugs: https://learnopengl.com/In-Practice/2D-Game/Collisions/Collision-resolution
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
		Ball->Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
		
		// We always know we have a collision on the top of the paddle
		//Ball->Velocity.y = -Ball->Velocity.y;
		Ball->Velocity.y = -1.0f * abs(Ball->Velocity.y);  		
		
		Ball->Velocity = glm::normalize(Ball->Velocity) * glm::length(oldVelocity);
	}
}

void Breakout::ProcessInput(double dt) {
	if (this->State == GAME_ACTIVE) {
		double velocity = PLAYER_VELOCITY * dt;

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