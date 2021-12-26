#include "main.h"

void intitialiserData(world_t* world){
    world->player_a = 1.8;
    world->player_x = 5;
    world->player_y = 6;
    world->exit = false;

    world->fps_lasttime = SDL_GetTicks(); //the last recorded time.
    world->fps_frames = 0; //frames passed since the last recorded fps.
}

void calculFPS(world_t* world){
    world->fps_frames++;
    if (world->fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
    {
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