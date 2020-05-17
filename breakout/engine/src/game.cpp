#include <iostream>

#include "engine/game.hpp"

// Must include full definition of engine
#include "engine/engine.hpp"

Game::Game(const int width, const int height, const std::string& _name) : State(GAME_MENU), Keys(), Width(width), Height(height), name(_name) {}

Game::~Game() {}

void Game::SetEngineDelegate(Engine* engine) {
    this->engine = engine;
	this->Width = engine->getScaledWidth();
	this->Height = engine->getScaledHeight();
}

void Game::Init() {}

void Game::Update(double dt) {}

void Game::DoCollisions() {}

void Game::ProcessInput(double dt) {}

void Game::pressed(int key) {}

void Game::released(int key) {}

void Game::Render() {}
