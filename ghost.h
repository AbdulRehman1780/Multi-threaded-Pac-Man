
#ifndef GHOST_H
#define GHOST_H

#include <stddef.h> 
#include <stdlib.h> 
#include <unistd.h>
#include <pthread.h>

#define GHOST_SPEED 500000
#define NUM_GHOSTS 4 

// Define the Ghost structure
typedef struct {
    int x;
    int y;
    // Add other attributes as needed
} Ghost;


// Define an array to hold ghost threads and ghost data
pthread_t ghostThreads[NUM_GHOSTS];
Ghost ghosts[NUM_GHOSTS];

// Function to control the behavior of a ghost
void* ghostController(void* arg) {
    // Retrieve the ghost's index
    int ghostIndex = *(int*)arg;
    
    // Infinite loop for ghost behavior
    while (1) {
        // Update ghost's position based on predefined movement or algorithm
        
        // Sleep for some time to control ghost speed
        usleep(GHOST_SPEED);
    }
    
    return NULL;
}

// Function to initialize ghosts
void initializeGhosts() {

    // Ghost 1
    ghosts[0].x = 2;
    ghosts[0].y = 2;

    // Ghost 2
    ghosts[1].x = 7;
    ghosts[1].y = 2;

    // Ghost 3
    ghosts[2].x = 2;
    ghosts[2].y = 7;

    // Ghost 4
    ghosts[3].x = 7;
    ghosts[3].y = 7;

    // Initialize other ghost attributes as needed
}


// Function to create ghost threads
void startGhostThreads() {
    int i;
    for (i = 0; i < NUM_GHOSTS; ++i) {
        // Pass the ghost's index as thread argument
        int* arg = malloc(sizeof(*arg));
        *arg = i;
        
        // Create thread for each ghost
        pthread_create(&ghostThreads[i], NULL, ghostController, arg);
    }
}

// Function to stop ghost threads
void stopGhostThreads() {
    // Cancel threads and perform cleanup
    for (int i = 0; i < NUM_GHOSTS; ++i) {
        pthread_cancel(ghostThreads[i]);
        // Additional cleanup if needed
    }
}





#endif
