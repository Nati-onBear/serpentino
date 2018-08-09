
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

// Map dimensions
const int MAP_WIDTH  = 20;
const int MAP_LENGTH = 40;
const int MAP_SIZE = MAP_WIDTH * MAP_LENGTH;

// Map array
int Map[MAP_SIZE];

// Snake head details
int headxpos;
int headypos;
int direction;

// The snake length
int bodyLength = 3;
// Score
int score = 0;
// Initial 0.3 second for sleep
int sec = 300;
// Determine if game is running
bool running = true;



// Returns graphical character for display from map value
char getMapValue(int value)
{
    // Returns a part of snake body
    if (value > 0) return '0';

    switch (value) {
        // Return vertical wall
    case -1: return '|';
        // Return honrizontal wall
    case -2: return '-';    
        // Return food
    case -3: return 'X';
    }
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

// Move the head to new position
void move(int dx, int dy, int n)
{
    // determine new head position
    int xNewPo = headxpos + dx;
    int yNewPo = headypos + dy;

    // Check if there is food at location
    if (Map[xNewPo + yNewPo * MAP_WIDTH] == -3) {
        // Increase body length and score
        bodyLength++;
        score++;
        // Increase speed
        if (sec > 50 && n == 1) {
		  sec -= 10;
		}

        // Generate new food on map
        generateFood();
    }

    // Check location is free
    else if (Map[xNewPo + yNewPo * MAP_WIDTH] != 0) {
        running = false;
    }

    // Move head to new location, increase by 1
    headxpos = xNewPo;
    headypos = yNewPo;
    Map[headxpos + headypos * MAP_WIDTH] = bodyLength + 1;

}

// Change direction from user input
void changeDirection(char key)
{

    switch (key) {
    case 'w': case 'W':
        if (direction != 1) direction = 0;
        break;
    case 's': case 'S':
        if (direction != 0) direction = 1;
        break;
    case 'd': case 'D':
        if (direction != 3) direction = 2;
        break;
    case 'a': case 'A':
        if (direction != 2) direction = 3;
        break;
    }
}

// Update the map after each move
void update(int n)
{
    // Move in direction indicated
    switch (direction) {
    case 0: move(-1, 0, n);
        break;
    case 1: move( 1, 0, n);
        break;
    case 2: move( 0, 1, n);
        break;
    case 3: move( 0,-1, n);
        break;
    }

    // Reduce snake values on map by 1
    for (int i = 0; i < MAP_SIZE; i++) {
        if (Map[i] > 0) Map[i]--;
    }
}


// Clear screen to continue
void clearScreen()
{
    // Clear the screen
    system("cls");
}

// Game over screen
void gameOver()
{
	Sleep(1000);
	clearScreen();
	
	// Print out game over text
    std::cout << "\n\n\t\t!GAME OVER!\n" << std::endl << "\t     Your score is: " << score;

    // Stop console from closing instantly
    std::cin.ignore();
}

// Loading screen
void load()
{
	int timer = 2000;
	std::cout << "\n\n\t\tLoading\n\t      ";
	for (int i = 1; i <= 11; i++) {
	 	printf("#");
	 	Sleep(timer);
	 	if (timer > 500) timer -= 500;
	}
}

void options()
{
	std::cout << "Choose your mode" << std::endl;
	std::cout << "0. Normal: The snake won't speed up'" << std::endl;
	std::cout << "1. Hard  : The snake will speed up" << std::endl;
}

void gui()
{
	printf ("\tWELCOME TO SERPENTINO \n");
    printf ("\n       PRESS ENTER TO CONTINUE");
    getchar();
	clearScreen();
	printf ("Playing with snake is easy  \n");
    printf ("Using w,a,s,d to control your snake \n");
    printf ("Control your snake to eat food on map \n");
	printf ("Hit the wall will let your snake go to heaven \n");
	printf ("WARNING: \n");
	printf ("PLEASE DON'T USE THE DIRECTION CONTRARY WITH YOUR SNAKE MOVING DIRECTION \n");
	printf ("PLAY SAFE AND DON'T EAT YOUR BODY PLEASE \n'");
	printf ("HAVE FUN \n");
	printf ("Press Enter to continue");
	getchar();
	clearScreen();
}

//main function printMap then clearMap loop
void run()
{
	int n;
	
    gui();
    
    options();
    std::cin >> n; 
    
    clearScreen();
	// Loading screen
	load();
    // Initialize the map
    initialMap();
    // While not hitting
    while (running == true) {
        // If a key is pressed
        if (kbhit()) {
            // Change to direction determined by key pressed
            changeDirection(getch());
        }
        // Upate the map
        update(n);

        // Clear the screen
        clearScreen();
        //clrscr();

        // Print the map
        printMap();

        // wait
        Sleep(sec);
    }

    gameOver();
}

int main()
{
    run();
    
    return 0;
}

