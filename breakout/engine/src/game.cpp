#include "engine/game.hpp"
#include <iostream>

Game::Game(const unsigned int width, const unsigned int height, const std::string& _name) : State(GAME_MENU), Keys(), Width(width), Height(height), name(_name) {}

Game::~Game() {}

void Game::SetEngineDelegate(Engine* engine) {
    this->engine = engine;
}

void Game::Init() {}

void Game::Update(float dt) {}

void Game::ProcessInput(float dt) {}

void Game::pressed(int key) {}

void Game::released(int key) {}

void Game::Render() {}
