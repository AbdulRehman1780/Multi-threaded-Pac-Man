# Multi-threaded-Pac-Man
Pac-Man Game

This is a simple implementation of the classic Pac-Man game using OpenGL and GLUT in C.
Description

The project consists of multiple C files:

    main.c: Contains the main game logic, including initialization, game loop, display rendering, and keyboard input handling.
    ghost.h: Header file defining the Ghost structure and functions related to ghost behavior.
    ghost.c: Source file containing the implementation of functions related to ghost behavior.
    game.h: Header file containing constant definitions and function prototypes used in the main game file (main.c).
    game.c: Source file containing functions related to game initialization, board rendering, pellet management, and collision detection.

Installation

    Ensure you have OpenGL and GLUT installed on your system.
    Compile the project using a C compiler such as GCC.

    bash

gcc main.c ghost.c game.c -o pacman -lGL -lglut -lm -lpthread

Run the compiled executable.

bash

    ./pacman

Usage

    Use the arrow keys to control Pac-Man's movement.
    Collect pellets to increase your score.
    Avoid colliding with ghosts, which will decrease your lives and score.

Contributors

    [Your Name]

License

This project is licensed under the MIT License.
