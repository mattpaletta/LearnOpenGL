//
//  Breakout.hpp
//  breakout
//
//  Created by Matthew Paletta on 2020-04-28.
//

#pragma once
#include <engine/game.hpp>
#include <iostream>

class Breakout;

class Breakout : public Game {
public:
    Breakout(const int width, const int height) : Game(width, height, "Breakout") {}

    void Init() override;
    void Render() override;
};
