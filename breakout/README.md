# Breakout

Implementation of Breakout Game.  Split into two libraries, the game code and the 2D engine built using OpenGL, OpenAL and FreeType.

Based on tutorials from: [LearnOpenGL Breakout](https://learnopengl.com/In-Practice/2D-Game/Breakout)

Features:
- Multiple levels
- Sound Effects
- Post Processing Effects
- Powerups
- Text Rendering
- Supports HiDPI Scaling

I followed along with the tutorials, but added the CMake file myself so it is buildable from a `Git Clone`.  Tested on Mac and Windows.  I separated the game code from the engine code, and made the code `const` correct, along with other minor optimizations.  I also added automatic display scaling for HiDPI devices.
