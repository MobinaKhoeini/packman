#include <conio.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define WIDTH 40 
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define DEMON 'X' 

int res = 0; 
int score = 0; 
int pacman_x, pacman_y; 
int food = 0; 
int curr = 0;  

typedef struct {
    int x;
    int y;
    char type;
} element;

element packman[HEIGHT][WIDTH];

void initialize() { 
    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            if (i == 0||j == (WIDTH - 1) || j == 0 || i == (HEIGHT - 1)) { 
                packman[i][j].type = WALL;
            }
             else {
                packman[i][j].type = EMPTY;
            }
            
        }
    }

    int count = 50; 
    while (count != 0) { 
        int i = rand() % HEIGHT; 
        int j = rand() % WIDTH; 
        if (packman[i][j].type != WALL && packman[i][j].type != PACMAN) { 
            packman[i][j].type = WALL;  
            count--; 
        } 
    }

    int val = 5; 
    while (val--) { 
        int row = rand() % HEIGHT; 
        for (int j = 3; j < WIDTH - 3; j++) { 
            if (packman[row][j].type != WALL && packman[row][j].type != PACMAN) {
                packman[row][j].type = WALL;
            } 
        } 
    } 

    count = 10; 
    while (count != 0) { 
        int i = rand() % HEIGHT; 
        int j = rand() % WIDTH; 

        if (packman[i][j].type != WALL && packman[i][j].type != PACMAN) { 
            packman[i][j].type = DEMON;
            count--; 
        } 
    } 

    pacman_x = HEIGHT / 2; 
    pacman_y = WIDTH / 2; 
    packman[pacman_x][pacman_y].type = PACMAN;

    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            if (i % 2 == 0 && j % 2 == 0 && packman[i][j].type == EMPTY) { 
                packman[i][j].type = FOOD;
                food++; 
            } 
        } 
    } 
} 

void draw() { 
    system("cls"); 
    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            printf("%c", packman[i][j].type);
        } 
        printf("\n"); 
    } 
    printf("Score: %d\n", score); 
} 

void move(int movex, int movey) { 
    int x = pacman_x + movex; 
    int y = pacman_y + movey; 

    if (packman[x][y].type != WALL) { 
        if (packman[x][y].type == FOOD) { 
            score++; 
            food--; 
            curr++; 
            if (food == 0) { 
                res = 2; 
                return; 
            } 
        } else if (packman[x][y].type == DEMON) { 
            res = 1; 
            return;
        } 
        packman[pacman_x][pacman_y].type = EMPTY;
        pacman_x = x; 
        pacman_y = y; 
        packman[pacman_x][pacman_y].type = PACMAN;
    } 
} 
void computerMode()
{
    int food_x = -1, food_y = -1;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (packman[i][j].type == FOOD)
            {
                food_x = i;
                food_y = j;
                break;
            }
        }
        if (food_x != -1)
            break;
    }
    if (food_x == -1)
        return;
    if (pacman_x < food_x)
    {
        move(1, 0);
    }
    else if (pacman_x > food_x)
    {
        move(-1, 0);
    }
    else if (pacman_y < food_y)
    {
        move(0, 1);
    }
    else if (pacman_y > food_y)
    {
        move(0, -1);
    }
}

int main()
{
    srand(time(0)); // Initialize random seed
    initialize();
    char ch;
    food -= 35;
    int totalFood = food;

    printf("Use buttons for w(up), a(left), d(right), and s(down)\nPress q to quit\n");
    printf("Enter Y to continue: \n");

    ch = getch();
    if (ch != 'Y' && ch != 'y')
    {
        printf("Exit Game! ");
        return 1;
    }
        {
    while (1)
    {
        printf("please choose your required option:\n");
        printf("1.Computer mode\n");
        printf("2.human mode\n");
        int Choice;
        scanf("%d", &Choice);
        switch (Choice)
    {
        case 1:
        while(1)
        {
             draw();
            printf("Total Food count: %d\n", totalFood);
            printf("Total Food eaten: %d\n", curr);
             if (res == 1)
            {
                // Clear screen
                system("cls");
                printf("Game Over! Dead by Demon\n Your Score: "
                       "%d\n",
                       score);
                return 1;
            }

            if (res == 2)
            {
                // Clear screen
                system("cls");
                printf("You Win! \n Your Score: %d\n", score);
                return 1;
            }
            computerMode();
        }
        break;
        case 2:
        while (1)
        {
            draw();
            printf("Total Food count: %d\n", totalFood);
            printf("Total Food eaten: %d\n", curr);   
            if (res == 1)
            {
                // Clear screen
                system("cls");
                printf("Game Over! Dead by Demon\n Your Score: "
                       "%d\n",
                       score);
                return 1;
            }

            if (res == 2)
            {
                // Clear screen
                system("cls");
                printf("You Win! \n Your Score: %d\n", score);
                return 1;
            }

        // Taking the Input from the user
        ch = getch();
        // Moving According to the
        // input character
        switch (ch)
        {
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
        break;
        default:
        printf("invalid choice!\n");
        break;
    }
    }

    return 0;
}

  
}
