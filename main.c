#include <stdio.h>
#include <stdlib.h>
#include "SpaceXplorer.h"

int main() {//here I declared all the main game objects
    Player player;//declaring variable, player, of a struct type Player
    Asteroid asteroid;
    Junk junk[MAX_JUNK];//declaration of an array of structures. junk is the name of array that holds multiple junk objects
    int junkCount;
    int gameOver = 0;
    char input;//ASK THE USER CHARACTER AS WORKING ON LINE 21 TO MOVE
    char name[MAX_NAME_LEN];//ASK THE USER CHARACTER AS WORKING ON LINE 32 FOR NAME

    loadIntro();
    int difficulty = getusersDifficulty();

    initialGamesetup(&player, &asteroid, junk, &junkCount, difficulty);//here i initialized the game setup
     while(!gameOver){//from here the main game starts within a loop//here the gameover is 0 initially which is false in c language but using !gameover this makes a fake condition anyway it's true now true, and its before it because it will countiune the loop until it founds the real gameover condition
         drawGrid(player, asteroid, junk, junkCount);
         printf("Move player using these keys(w,s,a,d):");
         scanf("%c", &input);//so whatever the user input is, the compiler will get here it will update this to

         movePlayer(&player);//this part and after player will move
         updateAsteroid(&asteroid, player, difficulty);//then it will move asteroid also
         checkCollision(&player, asteroid, junk, junkCount, &gameOver);//then it will check for any collision


        printf("[NOTE]:Check your Player at (%d, %d), Asteroid at (%d, %d)\n",
                  player.pos.x, player.pos.y, asteroid.pos.x, asteroid.pos.y);
} if (gameOver == 2){
         printf("Congratulations! You won the match\nEnter your name for leadership board");//after getting this message
         scanf("%s", name);//HERE IT ASK FOR NAME
        saveScores(name, player.score);//update the score automatically and add the name as already asked
     } else {
         printf("Game over! better luck next time");
     }
     return 0;
}