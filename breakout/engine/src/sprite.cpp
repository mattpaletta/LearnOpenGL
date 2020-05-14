//
//  sprite.cpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-29.
//

#include "engine/sprite.hpp"
#include "engine/debug.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <array>

constexpr std::array<float, 4 * 2 * 3> get_cube_vertices() {
    return {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };
}

SpriteRenderer::SpriteRenderer(Shader&& _shader) : shader(std::move(_shader)) {
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData() {
    // configure VAO/VBO
    unsigned int VBO;
    constexpr auto cube = get_cube_vertices();

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube.data()), cube.data(), GL_STATIC_DRAW);
    glCheckError();

    glBindVertexArray(this->quadVAO);
    glCheckError();

    glEnableVertexAttribArray(0);
    glCheckError();

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glCheckError();

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glCheckError();

    glBindVertexArray(0);
    glCheckError();
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size, const float& rotate, const glm::vec3& color) {
    // prepare transformations
    this->shader.use();
    glCheckError();

    glm::mat4 model{1.0f};

//    for (std::size_t i = 0; i < 4; ++i) {
//        for (std::size_t j = 0; j < 4; ++j) {
//            std::cout << model[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    model = glm::translate(model, glm::vec3(position, 0.0f));

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    // We've already 'set' it above.
    constexpr bool useShader = false;
    this->shader.setMat4("model", model, useShader);
    this->shader.setVec3("spriteColor", color, useShader);

    glActiveTexture(GL_TEXTURE0);
    glCheckError();
    texture.Bind();
    glCheckError();

    glBindVertexArray(this->quadVAO);
    glCheckError();

    glDrawArrays(GL_TRIANGLES, 0, 6);
    glCheckError();

    glBindVertexArray(0);
    glCheckError();
}
