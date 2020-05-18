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
#include "game_level.hpp"
#include "game_object.hpp"
#include "particle.hpp"
#include "particle_generator.hpp"
#include "text_renderer.hpp"

#include "audio.hpp"

#include <GLFW/glfw3.h>
#include <utility>
#include <memory>

class Engine {
private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    Game* game = nullptr;

    std::unique_ptr<SpriteRenderer> spriteRenderer = nullptr;
	AudioEngine audioEngine;
	TextRenderer textRenderer;

    double deltaTime = 0.0f;
    double lastFrame = 0.0f;
    
    // OpenGL Window
    GLFWwindow* window;

    void init_opengl();
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
public:
    Engine(Game& _g);
    Engine(const int width, const int height, Game& _g);
    ~Engine();

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;
	
	int getScaledWidth();
	int getScaledHeight();
	glm::vec2 scaleObj(const float& desired_width, const float& desired_height);
	float scaleObj(const float& desired_size);

    void resizeable(bool value);
    void setSpriteRendering(const std::string& resourceName);
	SpriteRenderer* getRenderer();
    void DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size = glm::vec2(10.0f, 10.0f), const float& rotate = 0.0f, const glm::vec3& color = glm::vec3(1.0f));

//    void set_framebuffer_size_callback();
//    void set_key_callback();
    void run();

	// Audio
	void LoadSound(const std::string& soundName, bool b3d = true, bool looping = false);
	void UnloadSound(const std::string& soundName);
	bool isLoaded(const std::string& soundName);
	void Play(const std::string& soundName);

	// Text
	TextRenderer& GetTextRenderer();
};
