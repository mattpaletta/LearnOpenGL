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

constexpr std::array<float, 4 * 4 * 3> get_cube_vertices() {
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

template<typename T, std::size_t N>
constexpr std::size_t get_raw_array_size(const std::array<T, N>& a) {
	return sizeof(T) * a.size();
}

SpriteRenderer::SpriteRenderer(const Shader& _shader) : shader(_shader) {
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData() {
    // configure VAO/VBO
    unsigned int VBO;
	constexpr auto vertices = get_cube_vertices();

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, get_raw_array_size(vertices) , vertices.data(), GL_STATIC_DRAW);
	
	glBindVertexArray(this->quadVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void SpriteRenderer::DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size, const float& rotate, const glm::vec3& color) {
    // prepare transformations
    this->shader.use();
    glCheckError();

    glm::mat4 model{1.0f};

	model = glm::translate(model, glm::vec3(position, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // last scale

    // We've already 'set' it above.
    this->shader.setMat4("model", model);
    this->shader.setVec3("spriteColor", color);

	glActiveTexture(GL_TEXTURE0);
    texture.Bind();
  
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
