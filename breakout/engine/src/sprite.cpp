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

constexpr std::array<float, 3 * 3 * 4> get_cube_vertices() {
    return {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
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
    unsigned int VBO, EBO;
    constexpr auto cube = get_cube_vertices();
	
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(this->quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube.data()), cube.data(), GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// position attribute
	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*) (0 * sizeof(float)));
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	this->shader.setInt("texture1", 0, true);

}

void SpriteRenderer::DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size, const float& rotate, const glm::vec3& color) {
    // prepare transformations
    //this->shader.use();
    //glCheckError();

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
    //constexpr bool useShader = false;
    //this->shader.setMat4("model", model, useShader);
    //this->shader.setVec3("spriteColor", color, useShader);
    this->shader.use();
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
  
	this->shader.use();
    glBindVertexArray(this->quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
