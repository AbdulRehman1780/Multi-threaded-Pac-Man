//#include "game.h"
#include "ghost.h"
#include <pthread.h>
#include <stdio.h>
#include <stddef.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <GL/glut.h>
#include <string.h>
#include <time.h>

// Constants to represent elements on the game board
#define MENU_OPTION_START 1
#define MENU_OPTION_PAUSE 2
#define MENU_OPTION_QUIT 3
#define WALL '#'
#define PATH ' '
#define PELLET '.'
#define POWER_PELLET 3
#define PACMAN 4
#define GHOST 5
#define LIFE 3
#define GHOST_SPEED 500000
#define MAX_USERNAME_LENGTH 50



// Size of the game board
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10


char username[MAX_USERNAME_LENGTH];

// Define the game board
int gameBoard[BOARD_HEIGHT][BOARD_WIDTH];

// Variables to store Pac-Man's position
int pacManX = 1;
int pacManY = 1;

// Game score
int score = 0;

// Lives count
int lives = 3; // Initial number of lives

enum MenuOptions {
    MENU_START,
    MENU_PAUSE,
    MENU_QUIT
};

void menu(int option) {
    switch (option) {
        case MENU_START:
            // Start the game
            glutSetWindowTitle("Game started.");
            break;
        case MENU_PAUSE:
            // Pause the game
            glutSetWindowTitle("Game paused.");
            break;
        case MENU_QUIT:
            // Quit the game
            glutSetWindowTitle("Game quit.");
            exit(0);
            break;
    }
}


void getUsername(int value) {
    switch (value) {
        case 0:
            // Initialize the game
            printf("Username: %s\n", username);
            break;
        case 1:
            // Quit the game
            exit(0);
            break;
    }
}

// Function to initialize the game board
void initializeGameBoard() {
    // Initialize the game board with walls and paths
    int initialBoard[BOARD_HEIGHT][BOARD_WIDTH] = {
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
        {WALL, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, WALL},
        {WALL, PATH, WALL, WALL, WALL, WALL, WALL, WALL, PATH, WALL},
        {WALL, PATH, WALL, PATH, PATH, PATH, PATH, WALL, PATH, WALL},
        {WALL, PATH, WALL, PATH, WALL, WALL, PATH, WALL, PATH, WALL},
        {WALL, PATH, PATH, PATH, PATH, PATH, PATH, PATH, PATH, WALL},
        {WALL, PATH, WALL, PATH, WALL, WALL, PATH, WALL, PATH, WALL},
        {WALL, PATH, WALL, PATH, PATH, PATH, PATH, WALL, PATH, WALL},
        {WALL, PATH, WALL, WALL, WALL, WALL, WALL, WALL, PATH, WALL},
        {WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
    };

    // Copy initial board layout to game board
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            gameBoard[i][j] = initialBoard[i][j];
        }
    }

    // Set Pac-Man starting position
    gameBoard[pacManY][pacManX] = PACMAN;
   
    
}

// Function to add pellets to the path on the game board
void addPellets() {
    // Seed the random number generator
    srand(time(NULL));

    // Iterate through the game board
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            // Check if the current cell is a path
            if (gameBoard[i][j] == PATH) {
                // Randomly decide whether to add a pellet to the path
                if (rand() % 4 == 0) { // Adjust the probability here (e.g., 1 in 4 chance)
                    gameBoard[i][j] = PELLET;
                }
            }
        }
    }
}

// Function to draw pellets on the game board
void drawPellets() {
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (gameBoard[i][j] == PELLET) {
                glColor3f(0.4, 0.4, 0.0); // Yellow color
                glRectf(j + 0.4, i + 0.4, j + 0.6, i + 0.6); // Draw a pellet at (i, j)
            }
        }
    }
}

// Function to render game elements
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the game board
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (gameBoard[i][j] == WALL) {
                // Draw wall
                glColor3f(0.0, 0.2, 0.0); // Green color
                glBegin(GL_QUADS);
                glVertex2f(j, i);
                glVertex2f(j + 1, i);
                glVertex2f(j + 1, i + 1);
                glVertex2f(j, i + 1);
                glEnd();
            } else if (gameBoard[i][j] == PACMAN) {
                // Draw Pac-Man
                glColor3f(1.0, 1.0, 0.0); // Yellow color
                glBegin(GL_QUADS);
                glVertex2f(j + 0.25, i + 0.25);
                glVertex2f(j + 0.75, i + 0.25);
                glVertex2f(j + 0.75, i + 0.75);
                glVertex2f(j + 0.25, i + 0.75);
                glEnd();
            } else if (gameBoard[i][j] == GHOST) {
                // Draw Ghost
                glColor3f(1.0, 0.0, 0.0); // Red color
                glBegin(GL_QUADS);
                glVertex2f(j + 0.25, i + 0.25);
                glVertex2f(j + 0.75, i + 0.25);
                glVertex2f(j + 0.75, i + 0.75);
                glVertex2f(j + 0.25, i + 0.75);
                glEnd();
            } else {
                // Draw path (empty cell)
                glColor3f(1.0, 1.0, 1.0);
                glBegin(GL_QUADS);
                glVertex2f(j, i);
                glVertex2f(j + 1, i);
                glVertex2f(j + 1, i + 1);
                glVertex2f(j, i + 1);
                glEnd();
            }
        }
    }

    // Draw pellets
    drawPellets();

    // Draw lives at the top-left corner
    glColor3f(0.0, 1.0, 0.0); // Green color
    for (int k = 0; k < lives; ++k) {
        glRectf(k * 0.1, 0.9, (k + 1) * 0.1, 1.0);
    }
    
    

    // Draw score at the top-right corner
    glColor3f(1.0, 1.0, 1.0); // White color
    char scoreStr[10];
    snprintf(scoreStr, 10, "Score: %d", score);
    glRasterPos2f(9.0, 0.9);
    int len = strlen(scoreStr);
    for (int k = 0; k < len; ++k) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, scoreStr[k]);
    }

    glutSwapBuffers();
}


// Function to handle keyboard input for Pac-Man movement
void keyboard(int key, int xx, int yy) {
    switch (key) {
        case GLUT_KEY_RIGHT:
            // Move Pac-Man right if the next cell is a path
            if (gameBoard[pacManY][pacManX + 1] == PATH || gameBoard[pacManY][pacManX + 1] == PELLET || gameBoard[pacManY][pacManX + 1] == GHOST) {
                // Check if the next cell contains a pellet
                if (gameBoard[pacManY][pacManX + 1] == PELLET) {
                    // If yes, remove the pellet and increase the score
                    gameBoard[pacManY][pacManX + 1] = PATH;
                    score++;
                }
                // Move Pac-Man
                gameBoard[pacManY][pacManX] = PATH;
                pacManX++;
                gameBoard[pacManY][pacManX] = PACMAN;
            }
            break;
        case GLUT_KEY_LEFT:
            // Move Pac-Man left if the next cell is a path
            if (gameBoard[pacManY][pacManX - 1] == PATH || gameBoard[pacManY][pacManX - 1] == PELLET || gameBoard[pacManY][pacManX - 1] == GHOST) {
                // Check if the next cell contains a pellet
                if (gameBoard[pacManY][pacManX - 1] == PELLET) {
                    // If yes, remove the pellet and increase the score
                    gameBoard[pacManY][pacManX - 1] = PATH;
                    score++;
                }
                // Move Pac-Man
                gameBoard[pacManY][pacManX] = PATH;
                pacManX--;
                gameBoard[pacManY][pacManX] = PACMAN;
            }
            break;
        case GLUT_KEY_UP:
            // Move Pac-Man up if the next cell is a path
            if (gameBoard[pacManY - 1][pacManX] == PATH || gameBoard[pacManY - 1][pacManX] == PELLET || gameBoard[pacManY - 1][pacManX] == GHOST) {
                // Check if the next cell contains a pellet
                if (gameBoard[pacManY - 1][pacManX] == PELLET) {
                    // If yes, remove the pellet and increase the score
                    gameBoard[pacManY - 1][pacManX] = PATH;
                    score++;
                }
                // Move Pac-Man
                gameBoard[pacManY][pacManX] = PATH;
                pacManY--;
                gameBoard[pacManY][pacManX] = PACMAN;
            }
            break;
        case GLUT_KEY_DOWN:
            // Move Pac-Man down if the next cell is a path
            if (gameBoard[pacManY + 1][pacManX] == PATH || gameBoard[pacManY + 1][pacManX] == PELLET || gameBoard[pacManY + 1][pacManX] == GHOST) {
                // Check if the next cell contains a pellet
                if (gameBoard[pacManY + 1][pacManX] == PELLET) {
                    // If yes, remove the pellet and increase the score
                    gameBoard[pacManY + 1][pacManX] = PATH;
                    score++;
                }
                // Move Pac-Man
                gameBoard[pacManY][pacManX] = PATH;
                pacManY++;
                gameBoard[pacManY][pacManX] = PACMAN;
            }
            break;
    }

    // Request redisplay to update the screen
    glutPostRedisplay();
}



// Function to update ghost positions on the game board with random movement
void updateGhostPositions() {
    // Iterate through each ghost
    for (int i = 0; i < NUM_GHOSTS; ++i) {
        // Randomly choose a direction (0: up, 1: down, 2: left, 3: right)
        int direction = rand() % 4;

        // Update the ghost's position based on the chosen direction
        switch (direction) {
            case 0: // Up
                if (ghosts[i].y > 0 && gameBoard[ghosts[i].y - 1][ghosts[i].x] != WALL) {
                    gameBoard[ghosts[i].y][ghosts[i].x] = PATH;
                    ghosts[i].y--;
                }
                break;
            case 1: // Down
                if (ghosts[i].y < BOARD_HEIGHT - 1 && gameBoard[ghosts[i].y + 1][ghosts[i].x] != WALL) {
                    gameBoard[ghosts[i].y][ghosts[i].x] = PATH;
                    ghosts[i].y++;
                }
                break;
            case 2: // Left
                if (ghosts[i].x > 0 && gameBoard[ghosts[i].y][ghosts[i].x - 1] != WALL) {
                    gameBoard[ghosts[i].y][ghosts[i].x] = PATH;
                    ghosts[i].x--;
                }
                break;
            case 3: // Right
                if (ghosts[i].x < BOARD_WIDTH - 1 && gameBoard[ghosts[i].y][ghosts[i].x + 1] != WALL) {
                    gameBoard[ghosts[i].y][ghosts[i].x] = PATH;
                    ghosts[i].x++;
                }
                break;
        }
        // Update the game board with the new ghost position
        gameBoard[ghosts[i].y][ghosts[i].x] = GHOST;
    }
}




void gameLoop() {
    // Update ghost positions
    updateGhostPositions();
    
    // Check for collision between Pac-Man and ghosts
for (int i = 0; i < NUM_GHOSTS; ++i) {
    if (pacManX == ghosts[i].x && pacManY == ghosts[i].y) {
        // Pac-Man collided with a ghost
        // Reset Pac-Man's position to the original position on the game board
        gameBoard[pacManY][pacManX] = PATH; // Clear current position
        pacManX = 1; // Reset X position
        pacManY = 1; // Reset Y position
        gameBoard[pacManY][pacManX] = PACMAN; // Update new position on the game board

        // Decrement the number of lives
        lives--;

        // Update the score (if desired)
        score -= 10; // Subtract 10 points for colliding with a ghost
    }
}

    
    // Request redisplay to update the screen
    glutPostRedisplay();
}




// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pac-Man Game");
    
     // Create the menu
    int usernameMenu = glutCreateMenu(getUsername);
    glutCreateMenu(menu);
    glutAddMenuEntry("Start", MENU_START);
    glutAddMenuEntry("Pause", MENU_PAUSE);
    glutAddMenuEntry("Quit", MENU_QUIT);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    //printf("Enter your username: ");
    //scanf("%s", username);
    
    srand(time(NULL));
    
    
    // Set OpenGL clear color and projection
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, BOARD_WIDTH, BOARD_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);
    
    
    // Initialize the game board
    initializeGameBoard();
    
    addPellets();
    
    // Initialize ghosts
    initializeGhosts();

    // Start ghost threads
    startGhostThreads();

    // Start the game loop
    gameLoop();
 

    // Stop ghost threads
    stopGhostThreads();
    
    // Set display function and keyboard function
    glutDisplayFunc(display);
    glutSpecialFunc(keyboard);
    
    // Set timer function to update game state
    glutTimerFunc(1000 / 60, gameLoop, 0);   
    
    // Enter GLUT event processing loop
    glutMainLoop();
    
    return 0;
}

