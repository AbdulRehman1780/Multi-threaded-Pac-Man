#include <stdio.h>
#include <GL/glut.h>

// Constants to represent elements on the game board
#define WALL 1
#define PATH 0
#define PELLET 2
#define POWER_PELLET 3
#define PACMAN 4
#define GHOST_HOUSE_ENTRANCE 5

// Size of the game board
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 10

// Extern declaration for gameBoard from main.c
extern int gameBoard[BOARD_HEIGHT][BOARD_WIDTH];

// Function to render game elements
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the game board
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        for (int j = 0; j < BOARD_WIDTH; ++j) {
            if (gameBoard[i][j] == WALL) {
                // Draw wall
                glColor3f(0.0, 0.0, 0.0); // Black color
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
            } else if (gameBoard[i][j] == GHOST_HOUSE_ENTRANCE) {
                // Draw ghost house entrance
                glColor3f(0.5, 0.5, 0.5); // Gray color
                glBegin(GL_QUADS);
                glVertex2f(j, i);
                glVertex2f(j + 1, i);
                glVertex2f(j + 1, i + 1);
                glVertex2f(j, i + 1);
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

    glutSwapBuffers();
}

// Main function
int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Pac-Man Game");

    // Set OpenGL clear color and projection
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, BOARD_WIDTH, BOARD_HEIGHT, 0);
    glMatrixMode(GL_MODELVIEW);

    // Set display function
    glutDisplayFunc(display);

    // Enter GLUT event processing loop
    glutMainLoop();

    return 0;
}

