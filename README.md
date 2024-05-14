# Multi-threaded-Pac-Man

This is a simple implementation of the classic Pac-Man game using OpenGL and GLUT in C.

## Description

The project consists of multiple C files:

- `gameEngine.c`: Contains the main game logic, including initialization, game loop, display rendering, and keyboard input handling.
- `ghost.h`: Header file defining the Ghost structure and functions related to ghost behavior.
- `ghostController.c`: Source file containing the implementation of functions related to ghost behavior.
- `userInterface.c`: Source file containing functions related to game initialization, board rendering, pellet management, and collision detection.

## Installation

1. Ensure you have OpenGL and GLUT installed on your system.
2. Compile the project using a C compiler such as GCC.

```bash
gcc gameEngine.c -o pacman -lGL -lglut -lm -lpthread
```

3. Run the compiled executable.

```bash
./pacman
```

## Usage

- Use the arrow keys to control Pac-Man's movement.
- Collect pellets to increase your score.
- Avoid colliding with ghosts, which will decrease your lives and score.

## Contributors

- [Abdul Rehman]
- [Ramish Shakeel]

## License

This project is licensed under the MIT License.
