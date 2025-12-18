#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SpaceXplorer.h"


void initialGamesetup(Player* player, Asteroid* asteroid, Junk junk[], int* junkCount, int difficulty) {//this is the game setup when the game will be uploaded AND INSIDE PARAMETERS ARE THE  FORMAL PARAMETERS
    srand(time(NULL));

    player->pos.x = GRID_SIZE / 2;
    player->pos.y = GRID_SIZE / 2;
    player->health = 100;
    player->score = 0;

    if (difficulty == 0){//from here to line 24 its difficulty level settings, condition
        player->fuel = 100;//USED ARROW TO FIRST DEREFRENCE IT THEN ACCESSING THE MEMBER OF THE STRUCT
        *junkCount =30;//easy version
    } else if (difficulty == 1){
        player->fuel = 80;
        *junkCount =20;//medium version
    } else if (difficulty == 2){
        player->fuel =80;
        *junkCount =25;//hard version
    }

    asteroid->pos.x = 0;//here the starting position of asteroid is at (0,0)
    asteroid->pos.y = 0;

    for (int i = 0; i < *junkCount; ++i) {// HERE *JUNKCOUNT IS A POINTER DEFREFRENCE; TAKE THE STORED VALUE IN JUNKCOUNT
        junk[i].pos.x = rand() % GRID_SIZE;
        junk[i].pos.y = rand() % GRID_SIZE;
        junk[i].active = 1;// active 1 is
    }
}

void drawGrid(Player player, Asteroid asteroid, Junk junk[], int junkCount) {
    for (int y = GRID_SIZE - 1; y >= 0; --y) {
        for (int x = 0; x < GRID_SIZE; ++x) {
            char symbol = '.';
            int isJunk = 0;

            for (int i = 0; i < junkCount; ++i)
                if (junk[i].active && junk[i].pos.x == x && junk[i].pos.y == y)
                    isJunk = 1;

            if (player.pos.x == x && player.pos.y == y)//here we are using the struct, so we used '.'
                symbol = 'S';
            else if (asteroid.pos.x == x && asteroid.pos.y == y && isJunk)
                symbol = '@';  // Asteroid on junk
            else if (asteroid.pos.x == x && asteroid.pos.y == y)
                symbol = 'A';
            else if (isJunk)
                symbol = 'J';

            printf("%c ", symbol);
        }
        printf("\n");
    }

    printf("Health: %d | Fuel: %d | Score: %d\n", player.health, player.fuel, player.score);
}
//void movePlayer(Player* player) {(version 1)

  //  char direction;
    //scanf("%c", &direction); // here we're reading a character

    //if (direction == 'w') {

      //  if (player->pos.y < GRID_SIZE - 1) { // when the player y coordinate is less than the grid size
        //    player->pos.y++;
        //}
    //} else if (direction == 's') {
//if (player->pos.y > 0) {
  //          player->pos.y--;
    //    }
    //} else if (direction == 'a') {

      //  if (player->pos.x > 0) {
        //    player->pos.x--;
        //}
    //} else if (direction == 'd') {

      //  if (player->pos.y < GRID_SIZE - 1) {
        //    player->pos.x++;
        //}

    //}
   // player->fuel -= 5;
//}

void movePlayer(Player* player) {//version2
    char direction;
    scanf(" %c", &direction); // Notice the space before %c to skip whitespace

    if (direction == 'w' && player->pos.y < GRID_SIZE - 1)
        player->pos.y++;
    else if (direction == 's' && player->pos.y > 0)
        player->pos.y--;
    else if (direction == 'a' && player->pos.x > 0)
        player->pos.x--;
    else if (direction == 'd' && player->pos.x < GRID_SIZE - 1)
        player->pos.x++;

    player->fuel -= 5;
}



void updateAsteroid(Asteroid* asteroid, Player player, int difficulty) {
    if(difficulty == 0) {//here according to difficulty level the user will select the asteroid movement will change
        asteroid->pos.x++;
        asteroid->pos.y++;
        if (asteroid->pos.x >= GRID_SIZE) {
            asteroid->pos.x = 0; // Reset to the left edge
        }

        if (asteroid->pos.y >= GRID_SIZE) {
            asteroid->pos.y = 0; // Reset to the top edge
        }

    }else if (difficulty == 1) {
        asteroid->pos.x++;
        asteroid->pos.y++;
        if (asteroid->pos.x >= GRID_SIZE) {
            asteroid->pos.x = 0; // Reset to the left edge
        }

        if (asteroid->pos.y >= GRID_SIZE) {
            asteroid->pos.y = 0; // Reset to the top edge
        }

    } else if (difficulty == 2) {
            if (asteroid->pos.x < player.pos.x)
                asteroid->pos.x++;
            else if (asteroid->pos.x > player.pos.x)
                asteroid->pos.x--;

            if (asteroid->pos.y < player.pos.y)
                asteroid->pos.y++;
            else if (asteroid->pos.y > player.pos.y)
                asteroid->pos.y--;
        }
    }


void checkCollision(Player* player, Asteroid asteroid, Junk junk[], int junkCount, int* gameOver) {//this function checks all the collisions
           player->pos.x, player->pos.y,//here it will check the asteroid and players position
           asteroid.pos.x, asteroid.pos.y;

    if (player->pos.x == asteroid.pos.x && player->pos.y == asteroid.pos.y) {//if both asteroid and player are onn same position
        printf("You were hit by the asteroid!\n");
        *gameOver = 1;
        return;
    }

    for (int i = 0; i < junkCount; ++i) {//it checks the player and junk on same position and when they are on same position....
        if (junk[i].active &&
            junk[i].pos.x == player->pos.x &&
            junk[i].pos.y == player->pos.y) {
            useJunk(player, &junk[i]);//the compiler will compile the usejunk function then
        }
    }

    if (player->fuel <= 0) {//check for the fuel level
        printf("You ran out of resources!\n");
        *gameOver = 1;//gameover =1 mean the game is over, because it is set
    }

    if (player->score >= 100) {//check for the score and here i said here that the score max need to be 100
        printf("Mission success! You cleaned up enough space junk.\n");
        *gameOver = 2;//here gameover =2 mean the player win
    }
}

void useJunk(Player* player, Junk* junk) {
    player->score += 10;
    player->fuel += 15;//why it increases by 10 because on the same time it is reducing 5 because of move it took
    if (player->fuel > 100) player->fuel = 100;
    junk->active = 0;//this mean the place, where the junk was active and junkactive was 1 is now empty
    printf("Yeppe! Collected junk! +10 score, +5 fuel.\n");
}

void saveScores(const char* name, int score) {
    FILE* file = fopen("scores.txt", "a");//this 'FILE' IS a pointer to a file named scores.txt saved in memory and opens in append mode(mean next line after one ends)
    if (file) {//here it checks whether the file is null or not//if not null
        fprintf(file, "%s: %d\n", name, score);//this condition will work with first name only
        fclose(file);//closes the file
    }
}

//version 1: i use this intially because i think using the same logic as save score can open the system file but it didn't
//void loadIntro() {
  //  FILE* file = fopen("intro.txt", "r");
    //if(file){
      //  printf(file);
    //}else {
      //  printf("Welcome to SpaceXplorer!\nGAME INSTRUCTIONS:\nIn this game there is a spaceship which is you denoted by 'S' and your task is to collect the junk(J) from space.\nEverytime you collect junk your fuel and the score will increase with +5 and +10 otherwise every move will cost you -10 fuel\nMovement Instructions(use these keys to move your spaceship):\nW = UP\nA = LEFT\nS = DOWN\nD = RIGHT\nNOTE: Please avoid hitting Asteroid(A)\n");
        //fclose(file);
   // }
//}

void loadIntro(){//yes its working with puts because using puts we directly just add the text as it is without error
    puts("Welcome to the SpaceXplorer game!\n"//refrence GeeksforGeeks (n.d.) puts() in C. Available from: https://www.geeksforgeeks.org/puts-vs-printf-for-printing-a-string/ [Accessed 8 May 2025]
         "In this game you are a spaceship (S) and your task is to collect the 10 junk pieces, denoted by (J).\n"
         "Each level has different difficulty levels, and before the game starts you have to select one level.\n"
         "Here are the game Manuals for spaceship movement:\n"
         "These are the keys you will use to move:\n"
         "W = UP\n"
         "S = D0WN\n"
         "A = LEFT\n"
         "D = RIGHT\n"
         "\n"
         "Every time when you collect the junk your fuel will increase with +5 and score with +10 but every move will cost you -5 fuel.\n"
         "Note:You have to avoid hitting the asteroid(A).");

}

//Difficulty getusersDifficulty(){(version 1: here initially I was using the advance version with enum but with this the player needs to be very specific so to make it easy, I choose the normal way of doing it
   // int choice;
   // printf("Choose any difficulty level(0= EASY, 1= MEDIUM, 2= HARD):");
  //  scanf("%d",&choice);

  //  if(choice <= 0 || choice <=2){
 //       printf("The game is loading %c\n", choice);
 //       return(Difficulty) choice;
//    }else {
 //       printf("Invalid choice, the game will set to easy level automatically\n");
//        return EASY;
//    }
//}
int getusersDifficulty() {
    int choice;
    printf("Choose any difficulty level (0 = EASY, 1 = MEDIUM, 2 = HARD): ");
    scanf("%d", &choice);

    // Check if the choice is valid
    if (choice == 0) {
        printf("Easy mode selected!\n");
        return 0; // EASY
    } else if (choice == 1) {
        printf("Medium mode selected!\n");
        return 1; // MEDIUM
    } else if (choice == 2) {
        printf("Hard mode selected!\n");
        return 2; // HARD
    } else {
        printf("Invalid choice, setting to Easy mode by default.\n");
        return 0; // Default to EASY if input is wrong
    }
}
