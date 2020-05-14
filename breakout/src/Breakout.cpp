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
	// configure shaders
	glm::mat4 projection = glm::ortho(
		0.0f, 
		static_cast<float>(this->Width),
		static_cast<float>(this->Height), 
		0.0f, 
		-1.0f, 
		1.0f);

	ResourceManager::GetShader("sprite").setInt("image", 0, true);
	ResourceManager::GetShader("sprite").setMat4("projection", projection);

	this->engine->setSpriteRendering("sprite");

	// load textures
	ResourceManager::LoadTexture("../textures/awesomeface.png", true, "face");
}

void Breakout::Render() {
    this->engine->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
