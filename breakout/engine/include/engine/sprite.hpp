//
//  sprite.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-29.
//
#pragma once

#include "shader.hpp"
#include "texture.hpp"

class SpriteRenderer {
private:
    Shader       shader;
    unsigned int quadVAO;

	// Initializes and configures the quad's buffer and vertex attributes
    void initRenderData();

public:
    SpriteRenderer(const Shader& shader);
    ~SpriteRenderer();

    void DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size = glm::vec2(10.0f, 10.0f), const float& rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f));
};
