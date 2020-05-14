#include "engine/game.hpp"
#include <iostream>

Game::Game(const int width, const int height, const std::string& _name) : State(GAME_MENU), Keys(), Width(width), Height(height), name(_name) {}

Game::~Game() {}

void Game::SetEngineDelegate(Engine* engine) {
    this->engine = engine;
}

void Game::Init() {}

void Game::Update(double dt) {}

void Game::ProcessInput(double dt) {}

void Game::pressed(int key) {}

void Game::released(int key) {}

void Game::Render() {}
