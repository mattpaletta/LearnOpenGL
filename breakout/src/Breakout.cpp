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
	/*
	const std::string spriteResource = "sprite";
    const std::string faceResource = "face";

    // load shaders
    ResourceManager::LoadShader("../src/sprite.vert", "../src/sprite.frag", "", spriteResource);

    // configure shaders
    glm::mat4 projection = glm::ortho(0.0f,
                                      (float) this->Width,
                                      (float) this->Height,
                                      0.0f,
                                      -2.0f,
                                      2.0f);
    ResourceManager::GetShader(spriteResource).use().setInt("image", 0, false);
    ResourceManager::GetShader(spriteResource).setMat4("projection", projection, false);
    // set render-specific controls
    this->engine->setSpriteRendering(spriteResource);

    // load textures
    ResourceManager::LoadTexture("../textures/container2.png", false, faceResource);
	*/
}

void Breakout::Render() {
    // this->engine->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
