#pragma once
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Engine;

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game {
protected:
    Engine* engine;
public:
    // game state
    GameState    State;
    bool         Keys[1024];
    int Width, Height;
    std::string name;
    
    // constructor/destructor
    Game(const int width, const int height, const std::string& _name);
    ~Game();

    // Delete move and copy operators.
    Game(const Game& g) = delete;
    Game& operator=(Game& g) = delete;

    Game(Game&& g) = delete;
    Game& operator=(Game&& g) = delete;

    // initialize game state (load all shaders/textures/levels)
    virtual void Init();

    void SetEngineDelegate(Engine* engine);

    // game loop
    virtual void ProcessInput(double dt);
    virtual void Update(double dt);
    virtual void Render();

    virtual void pressed(int key);
    virtual void released(int key);
};
