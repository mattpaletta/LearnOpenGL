//
//  engine.cpp
//  engine
//
//  Created by Matthew Paletta on 2020-04-28.
//

#include "engine/engine.hpp"
#include "engine/debug.hpp"

#include <glad/glad.h>

// Helper function for opengl
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    glCheckError();
}

Engine::Engine(Game& _g) : SCREEN_WIDTH(_g.Width), SCREEN_HEIGHT(_g.Height), game(&_g) {
    this->init_opengl();
}

Engine::Engine(const std::size_t& width, const std::size_t& height, Game& _g) : SCREEN_WIDTH(width), SCREEN_HEIGHT(height), game(&_g), spriteRenderer() {
    this->init_opengl();
}

Engine::~Engine() {
    this->game->SetEngineDelegate(nullptr);
}

void Engine::setSpriteRendering(const std::string& resourceName) {
    this->spriteRenderer = std::make_unique<SpriteRenderer>(std::move(ResourceManagerGetShader(resourceName)));
}

void Engine::DrawSprite(const Texture2D& texture, const glm::vec2& position, const glm::vec2& size, const float& rotate, const glm::vec3& color) {
    if (this->spriteRenderer) {
        this->spriteRenderer->DrawSprite(texture, position, size, rotate, color);
    } else {
//#if DEBUG
        std::cout << "Failed to find spriteRenderer" << __FILE__ << __LINE__ << std::endl;
//#endif
    }
}

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    // When a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            // Update 'pressed' after the bool array
            this->game->Keys[key] = true;
            this->game->pressed(key);

        } else if (action == GLFW_RELEASE) {
            this->game->Keys[key] = false;
            this->game->released(key);
        }
    }
}

void Engine::init_opengl() {
    // Initialize OpenGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

#if DEBUG
//   glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif?

    // Default to false
    this->resizeable(false);

    this->window = glfwCreateWindow(this->SCREEN_WIDTH, this->SCREEN_HEIGHT, this->game->name.c_str(), nullptr, nullptr);
    if (this->window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(this->window);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		throw std::runtime_error("Failed to initialize GLAD");
	}

    // Hack to get the engine to register
    glfwSetWindowUserPointer(this->window, this);
    auto key_callback_lambda = [](GLFWwindow* window, int key, int scancode, int action, int mode) {
        Engine* e = static_cast<Engine*>(glfwGetWindowUserPointer(window));
        e->key_callback(window, key, scancode, action, mode);
    };

    glfwSetKeyCallback(this->window, key_callback_lambda);
    glfwSetFramebufferSizeCallback(this->window, framebuffer_size_callback);

    

    // OpenGL configuration
    // --------------------
    glViewport(0, 0, this->SCREEN_WIDTH, this->SCREEN_HEIGHT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Engine::resizeable(bool value) {
    glfwWindowHint(GLFW_RESIZABLE, value);
}

void Engine::run() {
	this->deltaTime = 0.f;
	this->lastFrame = 0.f;

	// Do the game loop
    while (!glfwWindowShouldClose(this->window)) {
        // calculate delta time
        // --------------------
        float currentFrame = glfwGetTime();
        this->deltaTime = currentFrame - lastFrame;
        this->lastFrame = currentFrame;
        glfwPollEvents();

        // manage user input
        // -----------------
        this->game->ProcessInput(deltaTime);
        glCheckError();

        // update game state
        // -----------------
        this->game->Update(deltaTime);
        glCheckError();

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        this->game->Render();
        glCheckError();

        glfwSwapBuffers(this->window);
    }

    // delete all resources as loaded using the resource manager
    // ---------------------------------------------------------
    ResourceManager::Clear();

    glfwTerminate();
}
