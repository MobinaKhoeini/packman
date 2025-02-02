#include <stdio.h> 
#include <conio.h>
#include <stdlib.h> 
#include <time.h>
// All the elements to be used 
// Declared here 
#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'S' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define DEMON 'X' 

// Global Variables are 
// Declared here 
int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
int food = 0; 
int curr = 0;  
typedef struct
{
	int x;
	int y;
	char type;
} element;
element packman[HEIGHT][WIDTH];
void initialize() 
{ 
	// Putting Walls as boundary in the Game 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i==0 || j==WIDTH-1 || j==0 || i==HEIGHT-1) { 
				packman[i][j].type = WALL;
			} 
			else
			{
				packman[i][j].type=EMPTY;
		}
		}
	} 

	// Putting Walls inside the Game 
	int count = 50; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT-2))+1; 
		int j = (rand() % (WIDTH-2))+1; 
		if (packman[i][j].type!=WALL && packman[i][j].type!=PACMAN)
		{ 
	    { 
			packman[i][j].type=WALL;	
			count--; 
		} 
		} 
	}

	/*
	int val = 5; 
    printf("l");
	while (val--) { 
        printf("a");
		int row = (rand() % (HEIGHT + 1)); 
		for (int j = 3; j < WIDTH - 3; j++) { 
			if (packman[row][j].type != WALL&& packman[row][j].type != PACMAN)
			{
                printf("b");
				packman[row][j].type= WALL;
			} 
            printf("c");
		} 
	} 
	*/

	// Putting Demons in the Game 
	count = 10; 
	while (count != 0) { 
		int i = (rand() % (HEIGHT-2))+1; 
		int j = (rand() % (WIDTH-2))+1; 

		if (packman[i][j].type!=WALL && packman[i][j].type!=PACMAN) { 
			packman[i][j].type=DEMON; 
			count--; 
		} 
	} 

	// Cursor at Center 
	pacman_x = HEIGHT / 2; 
	pacman_y = WIDTH / 2; 
	packman[pacman_x][pacman_y].type=PACMAN;
	// Points Placed 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			if (i % 2 == 0 && j % 2 == 0 &&
				packman[i][j].type==EMPTY) { 

				packman[i][j].type=FOOD;
				food++; 
			} 
		} 
	} 
} 

void draw() 
{ 
	// Clear screen 
	system("cls"); 

	// Drawing All the elements in the screen 
	for (int i = 0; i < HEIGHT; i++) { 
		for (int j = 0; j < WIDTH; j++) { 
			printf("%c", packman[i][j].type);
		} 
		printf("\n"); 
	} 
	printf("Score: %d\n", score); 
} 

// Function enables to move the Cursor 
void move(int move_x, int move_y) 
{ 
	int x = pacman_x + move_x; 
	int y = pacman_y + move_y; 
	//if(x>=0 && x<HEIGHT && y>=0 && y<WIDTH)
	//{
	if (packman[x][y].type != WALL) { 
		if (packman[x][y].type ==FOOD) { 
			score++; 
			food--; 
			curr++; 
			if (food == 0) { 
				res = 2; 
				return; 
			} 
		}
	} 
		else if (packman[x][y].type==DEMON) { 
			res = 1; 
			return;
		} 
		packman[pacman_x][pacman_y].type = EMPTY;
		pacman_x = x; 
		pacman_y = y; 
		packman[pacman_x][pacman_y].type=PACMAN;
	//} 
} 

// Main Function 
int main() 
{ 
	srand(time(NULL));
	initialize(); 
	char ch; 
	food -= 35; 
	int totalFood = food; 
	// Instructions to Play 
	printf(" Use buttons for w(up), a(left) , d(right) and "
		"s(down)\nAlso, Press q for quit\n"); 

	printf("Enter Y to continue: \n"); 

	ch = getch(); 
	if (ch != 'Y' && ch != 'y') { 
		printf("Exit Game! "); 
		return 1; 
	} 

	while (1) { 
		draw(); 
		printf("Total Food count: %d\n", totalFood); 
		printf("Total Food eaten: %d\n", curr); 
		if (res == 1) { 
			// Clear screen 
			system("cls"); 
			printf("Game Over! Dead by Demon\n Your Score: "
				"%d\n", 
				score); 
			return 1; 
		} 

		if (res == 2) { 
			// Clear screen 
			system("cls"); 
			printf("You Win! \n Your Score: %d\n", score); 
			return 1; 
		} 

		// Taking the Input from the user 
		ch = getch(); 

		// Moving According to the 
		// input character 
		switch (ch) { 
		case 'w': 
			move(0, -1); 
			break; 
		case 's': 
			move(0, 1); 
			break; 
		case 'a': 
			move(-1, 0); 
			break; 
		case 'd': 
			move(1, 0); 
			break; 
		case 'q': 
			printf("Game Over! Your Score: %d\n", score); 
			return 0; 
		} 
	} 

	return 0; 
}
