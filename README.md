# park-man
My take on the classic arcade Pac-Man game, made with SDL2

## Summary
This is my capstone project for the Udacity C++ nanodegree program.
I chose Capstone option 1, developing a video game that I started from scratch.
The video game is a basic version of the arcade classic, Pac-Man.
It reads a maze from a file and displays the Player character as well as the Ghosts.
Ghosts will kill the player when they collide with it.
The player wins the game when it collects all the dots in the maze.
Arrow keys are the only controls and can be used to move the player around.

## Prerequisites for Building
* cmake >= 3.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image >= 2.0
  * All installation instructions can be found [here](https://www.libsdl.org/projects/SDL_image/)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_ttf >= 2.0
  * All installation instructions can be found [here](https://www.libsdl.org/projects/SDL_ttf/)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.

## File and class structure
Game is the class that implements the game loop and manages typical game systems and modules, such as Controller, Renderer or GUI.
The Board class represents the level tile map. Both the Enemy and Player classes represent the entities in game, and are composed of Animations, which are represented through Textures and quads.
The GUI class also renders text using a Texture.

## Source materials
I used the [04b03](https://www.whatfontis.com/04b03.font) ttf font, which is free for personal use.
Everything else used to make this project is my own material (other than the aforementioned libraries and tools, of course).

## Rubric points
This project addresses the following rubric points:
* A README with instructions is included with the project
* The README indicates which project is chosen.
* The README includes information about each rubric point addressed.
* The submission must compile and run.
* The project demonstrates an understanding of C++ functions and control structures.
* The project reads data from a file and process the data, or the program writes data to a file. (Board::LoadFromFile)
* The project accepts user input and processes the input. (Controller::HandleInput)
* The project uses Object Oriented Programming techniques.
* Classes use appropriate access specifiers for class members.
* Class constructors utilize member initialization lists.
* The project makes use of references in function declarations. (Board::GetTile and Player::HandleEnemyCollisions)
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
* The project uses smart pointers instead of raw pointers.