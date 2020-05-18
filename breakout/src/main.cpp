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
    const auto b = std::make_shared<Breakout>(screen_width, screen_height);

    Engine e{b};
	// Game.Init() is called in the constructor

    // Start drawing the frames
    e.run();
	return 0;
}

