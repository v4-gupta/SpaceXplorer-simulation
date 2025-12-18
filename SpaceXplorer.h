#ifndef SpaceXplorer_h
#define SpaceXplorer_h

#define GRID_SIZE 18 //define is a pre-processor command which is saving the grid_size data in memory(hardware) as a binary
#define MAX_JUNK 50
#define MAX_NAME_LEN 50

//typedef enum { EASY, MEDIUM, HARD} Difficulty;//inside the brackets are label and enum assign integer value to these labels automatically(part of version 1)

typedef struct {
    int x, y;
} Position;//here the position is a name of typedef structure

typedef struct{
    Position pos;//here no variable these are just labels to the struct name Player
    int fuel;// these are the members of the struct
    int health;
    int score;
} Player;

typedef struct{
    Position pos;
} Asteroid;

typedef struct{
    Position pos;
    int active;
} Junk;

//void initialGamesetup(Player* player, Asteroid* asteroid, Junk junk[], int* junkCount, Difficulty difficulty);//PROTOTYPE
void initialGamesetup(Player* player, Asteroid* asteroid, Junk junk[], int* junkCount, int difficulty);//PROTOTYPE with formal parameters
void drawGrid(Player player, Asteroid asteroid, Junk junk[], int junkCount);
void movePlayer(Player* player);
void updateAsteroid(Asteroid* asteroid,Player player, int difficulty);
void checkCollision(Player* player, Asteroid asteroid, Junk junk[], int junkCount, int* gameOver);
void useJunk(Player* player, Junk* junk);
void saveScores(const char* name, int score);
void loadIntro();
int getusersDifficulty();

#endif