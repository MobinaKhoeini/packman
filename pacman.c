#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define WIDTH 40
#define HEIGHT 20
#define PACMAN 'C'
#define WALL '#'
#define FOOD '.'
#define EMPTY ' '
#define DEMON 'X'
#define ENEMY 'E'
#define SPEED '$' 
int res = 0;
int score = 0;
int pacman_x, pacman_y;
int enemy_x,enemy_y;
int food = 0;
int curr = 0;
int speedCount;
int totalSpeed=10;

typedef struct
{
    int x;
    int y;
    char type;
} element;

element packman[HEIGHT][WIDTH];

void initialize()
{
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == 0 || j == (WIDTH - 1) || j == 0 || i == (HEIGHT - 1))
            {
                packman[i][j].type = WALL;
            }
            else
            {
                packman[i][j].type = EMPTY;
            }
        }
    }
    enemy_x = rand() % (HEIGHT-2)+1;
        enemy_y= rand() % (WIDTH-2)+1;

        if (packman[enemy_x][enemy_y].type != WALL && packman[enemy_x][enemy_y].type != PACMAN)
        {
            packman[enemy_x][enemy_y].type = ENEMY;
        }
    int count = 50;
    while (count != 0)
    {
        int i = rand() % HEIGHT;
        int j = rand() % WIDTH;
        if (packman[i][j].type != WALL && packman[i][j].type != PACMAN && packman[i][j].type != ENEMY)
        {
            packman[i][j].type = WALL;
            count--;
        }
    }

    int val = 5;
    while (val--)
    {
        int row = rand() % HEIGHT;
        for (int j = 3; j < WIDTH - 3; j++)
        {
            if (packman[row][j].type != WALL && packman[row][j].type != PACMAN && packman[row][j].type != ENEMY)
            {
                packman[row][j].type = WALL;
            }
        }
    }

    count = 10;
    while (count != 0)
    {
        int i = rand() % HEIGHT;
        int j = rand() % WIDTH;

        if (packman[i][j].type != WALL && packman[i][j].type != PACMAN && packman[i][j].type != ENEMY)
        {
            packman[i][j].type = DEMON;
            count--;
        }
    }

    pacman_x = HEIGHT / 2;
    pacman_y = WIDTH / 2;
    packman[pacman_x][pacman_y].type = PACMAN;

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i % 2 == 0 && j % 2 == 0 && packman[i][j].type == EMPTY)
            {
                packman[i][j].type = FOOD;
                food++;
            }
        }
    }
    for(int i=0; i<5; i++)
    {
        int Speed_x= rand()%(HEIGHT-2)+1;
        int Speed_y= rand()%(WIDTH-2)+1;
        if(packman[Speed_x][Speed_y].type==EMPTY)
        {
            packman[Speed_x][Speed_y].type=SPEED;
        }
    }
}

void draw()
{
    system("cls");
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            printf("%c", packman[i][j].type);
        }
        printf("\n");
    }
    printf("Score: %d\n", score);
}
void enemyMove()
{
    int move_x=0;
    int move_y=0;
    int direction=rand()%4;
    switch (direction)
    {
        case 0:
        {
            move_x=-1; move_y=0;
        } break;
        case 1:
        {
            move_x=1; move_y=0;
        } break;
        case 2:
        {
            move_x=0; move_y=-1;
        } break;
        case 3:
        {
            move_x=0; move_y=1;
        } break;
    }
        int new_x = enemy_x + move_x;
        int new_y = enemy_y + move_y;
        if(packman[new_x][new_y].type!=WALL)
        {
            packman[enemy_x][enemy_y].type=EMPTY;
            enemy_x = new_x;
            enemy_y = new_y;
            packman[enemy_x][enemy_y].type=ENEMY;
        }
        if(pacman_x==enemy_x && pacman_y==enemy_y)
        {
            res=3;
        }
}

void move(int move_x, int move_y)
{
    if(speedCount>0)
    {
        move_x*=2;
        move_y*=2;
        speedCount--;
    }
    int x = pacman_x + move_x;
    int y = pacman_y + move_y;

    if (packman[x][y].type != WALL)
    {
        if (packman[x][y].type == FOOD)
        {
            score++;
            food--;
            curr++;
            if (food == 0)
            {
                res = 2;
                return;
            }
        }
        else if (packman[x][y].type == DEMON)
        {
            res = 1;
            return;
        }
        else if (packman[x][y].type == ENEMY)
        {
            res = 3;
            return;
        }
        else if (packman[x][y].type == SPEED)
        {
            speedCount = totalSpeed ;
            packman[x][y].type == EMPTY ;
        }
        packman[pacman_x][pacman_y].type = EMPTY;
        pacman_x = x;
        pacman_y = y;
        packman[pacman_x][pacman_y].type = PACMAN;
    }
}
void computerMode()
{
    enemyMove();
    int move_x=0;
    int move_y=0;
    int direction=rand()%4;
    switch (direction)
    {
        case 0:
        {
            move_x=-1; move_y=0;
        } break;
        case 1:
        {
            move_x=1; move_y=0;
        } break;
        case 2:
        {
            move_x=0; move_y=-1;
        } break;
        case 3:
        {
            move_x=0; move_y=1;
        } break;
    }
        move(move_x,move_y);
}
void saveGame() {
    FILE *file = fopen("D:/saveBinary.c.txt", "wb");
    if(file==NULL)
    {
        printf("Error saving the game!\n");
        return;
    }
    
    fprintf(file, "%d %d %d %d %d %d %d\n", pacman_x, pacman_y, enemy_x, enemy_y, score, food, curr);
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                fprintf(file, "%c", packman[i][j].type);
            }
            fprintf(file, "\n");
        }
        fclose(file);
        printf("Game saved successfully!\n");  
        return ;
}
void loadGame() {
    FILE *file = fopen("D:/pacmanSave.txt", "r");
    if (file == NULL) {
        printf("No saved game found. Starting a new game.\n");
        return;
    }

    
    fscanf(file, "%d %d %d\n", &score, &food, &curr); 
      
       for (int i = 0; i < HEIGHT; i++) 
       {
           for (int j = 0; j < WIDTH; j++) 
           {
               fscanf(file, "%c ", &packman[i][j].type);
           }
            fscanf(file, "\n");
       }
       

    fclose(file);
    printf("Game loaded successfully!\n");
    res=0;
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
    while (1)
    {
        printf("please choose your required option:\n");
        printf("1.Computer mode\n");
        printf("2.human mode\n");
        if(speedCount > 0)
        {
             printf("%d time(s) to double move\n" ,speedCount);
        }

        int Choice;
        scanf("%d", &Choice);
        switch (Choice)
        {
        case 1:
        {
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
                
                computerMode();
                Sleep(1000);
            }
        }
        break;
        case 2:
        {
            while (1)
            {
                printf("Do you want to play the previous game?(Y/N)\n");

               ch = getch();
               if (ch == 'Y' || ch == 'y')
               {
               loadGame();
               totalFood = food;
    }
                draw();
                printf("Total Food count: %d\n", totalFood);
                printf("Total Food eaten: %d\n", curr);
                if(speedCount > 0)
        {
             printf("%d time(s) to double move\n" ,speedCount);
        }
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
                    move(-1, 0);
                    break;
                case 's':
                    move(1, 0);
                    break;
                case 'a':
                    move(0, -1);
                    break;
                case 'd':
                    move(0, 1);
                    break;
                case 'q':
                    printf("Game Over! Your Score: %d\n", score);
                    return 0;
                }
                enemyMove();
                if (res == 3)
                {
                    // Clear screen
                    system("cls");
                    printf("Game Over! Dead by Enemy\n Your Score: "
                           "%d\n",
                           score);
                    return 1;
                }
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
