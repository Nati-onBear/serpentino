#include <iostream>
#include <conio.h>
#include <stdlib.h>

// Map dimensions
const int MAP_WIDTH  = 20;
const int MAP_LENGTH = 40;
const int MAP_SIZE = MAP_WIDTH * MAP_LENGTH;

// Map array
int Map[MAP_SIZE];

// Returns graphical character for display from map value
char getMapValue(int value)
{

    switch (value) {
        // Return vertical wall
    case -1: return '|';
        // Return honrizontal wall
    case -2: return '-';    
        // Return food
    case -3: return 'X';

}


// Print the map
void printMap()
{
    for (int x = 0; x < MAP_WIDTH; ++x) {
        for (int y = 0; y < MAP_LENGTH; ++y) {
            // Prints the value at current x,y location
            std::cout << getMapValue(Map[x + y * MAP_WIDTH]);
        }
        // Newline
        std::cout << std::endl;
    }
}

// Initialize the map and snake position
void initialMap()
{
    // Places the initial head location in middle of map
    headxpos = MAP_WIDTH  / 2;
    headypos = MAP_LENGTH / 2;
    Map[headxpos + headypos * MAP_WIDTH] = 1;

    // Places left and right walls 
    for (int x = 0; x < MAP_WIDTH; ++x) {
        Map[x] = -1;
        Map[x + (MAP_LENGTH - 1) * MAP_WIDTH] = -1;
    }

    // Places top and bottom walls
    for (int y = 0; y < MAP_LENGTH; y++) {
        Map[0 + y * MAP_WIDTH] = -2;
        Map[(MAP_WIDTH - 1) + y * MAP_WIDTH] = -2;
    }

    // Generates first food
    generateFood();
}

// Make food
void generateFood()
{
    int xFood = 0;
    int yFood = 0;
    srand (time(NULL));//Truly random
    do {
    	
        // Generate random x and y values within the map
        xFood = rand() % (MAP_WIDTH - 2) + 1;
        yFood = rand() % (MAP_LENGTH - 2) + 1;

        // If location is not free try again
    } while (Map[xFood + yFood * MAP_WIDTH] != 0);

    // Place new food
    Map[xFood + yFood * MAP_WIDTH] = -3;
}


