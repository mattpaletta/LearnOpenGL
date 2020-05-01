//
//  engine.hpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#pragma once

// Include everything from the engine
#include "game.hpp"
#include "resource.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "sprite.hpp"

#include <GLFW/glfw3.h>
#include <utility>
#include <memory>

class Engine {
private:
    std::size_t SCREEN_WIDTH;
    std::size_t SCREEN_HEIGHT;
    Game* game = nullptr;

    std::unique_ptr<SpriteRenderer> spriteRenderer = nullptr;

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    
    // OpenGL Window
    GLFWwindow* window;

    void init_opengl();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
public:
    Engine(Game& _g);
    Engine(const std::size_t& width, const std::size_t& height, Game& _g);
    ~Engine();
    void resizeable(bool value);
    void setSpriteRendering(const std::string& resourceName);
    void DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size = glm::vec2(10.0f, 10.0f), const float& rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f));

//    void set_framebuffer_size_callback();
//    void set_key_callback();
    void run();
};
