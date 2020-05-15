#include "engine/engine.hpp"

#include "breakout.hpp"

#include <utility>
#include <memory>


int main() {
#if DEBUG
    std::cout << "Starting Debug" << std::endl;
#endif

    constexpr int screen_width = 800;
    constexpr int screen_height = 600;
    Breakout b{screen_width, screen_height};

    Engine e{b};
    b.SetEngineDelegate(&e);

    // Configure the game
    b.Init();
	void DoCollisions(); void DoCollisions(); void DoCollisions(); void DoCollisions();







    //b.State = GAME_MENU;
	b.State = GAME_ACTIVE;

    // Start drawing the frames
    e.run();
	return 0;
}

