#include "main.h"
#include <fcntl.h>
#include <unistd.h>
void intitialiserData(world_t* world){
    createMap(world);

    world->player_a = 1.8;
    world->player_x = 2;
    world->player_y = 2;
    world->score = 0;
    world->exit = false;
    world->continuer = false;
    world->objectif = false;
    world->graphisme = false;
    world->graphismeOption = .002;
    world->graphismeOptionRayon = 512;
    world->graphismeOptionWidth = 1;
    world->tonyMort = false;
    world->fps_lasttime = SDL_GetTicks(); 
    world->fps_frames = 0; 
    world->fps_current = 0; 

    world->ammo.x = 1280/2 + 70;
    world->ammo.y = 720/2 + 80;
    world->ammo.w = AMMO_WIDTH;
    world->ammo.h = AMMO_HEIGHT;

    world->ammoShooted = false;
    world->compteurNbreImpact = 0;
    world->difficulte = 0;
}

void calculFPS(world_t* world){
    world->fps_frames++;
    if (world->fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000){
        world->fps_lasttime = SDL_GetTicks();
        world->fps_current = world->fps_frames;
        world->fps_frames = 0;
    }
}

bool testMur(world_t* world) {
    if (world->map[(int)world->player_y][(int)world->player_x] != ' ') {
        return true;
    }
    return false;
}

void testCollision(world_t* world){
    if (testMur(world)){ 
        world->player_x = world->ancienPlayer_x;
        world->player_y = world->ancienPlayer_y;
    }
}

void setMonstre(world_t* world) {
    srand(time(NULL));

    for (short i = 0; i < world->difficulte; i++){
        world->monstre[i].xMap = 0;
        world->monstre[i].yMap = 0;
        while (world->monstre[i].xMap == 0 || world->monstre[i].yMap == 0){
            short random_x = rand() % 14 + 1;
            short random_y = rand() % 14 + 1;
            if (world->map[random_y][random_x] == ' '){
                world->monstre[i].xMap = random_x ;
                world->monstre[i].yMap = random_y ;
            }
        }
    }
}


void ecrireScore(world_t* world) {
    FILE* f;
    f = fopen("score.txt", "w");
    fprintf(f,"%d", world->score);
    fclose(f);
}



void ancienCoord(world_t* world) {
    world->ancienPlayer_x = world->player_x;
    world->ancienPlayer_y = world->player_y;
}