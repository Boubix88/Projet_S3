#include "main.h"

void createMap(world_t* world){
  char map[16][16] = {"1111111111111111",
                      "1   11   11   11",
                      "1   11   11 2 11",
                      "11 1111 1111 111",
                      "1    2         1",
                      "11111111111111 1",
                      "1  1     2   1 1",
                      "1  1   1 11  1 1",
                      "1    1   2   1 1",
                      "111  1 1  1  1 1",
                      "1      1 1   1 1",
                      "1  1 1 1       1",
                      "1  1       1   1",
                      "1    1  1 1  1 1",
                      "1     1      1 1",
                      "1111111111111111"}; 
                      
  for (int i = 0; i < 16; i++){
    for (int j = 0; j < 16; j++){
      world->map[i][j] = map[i][j];
    }
  }
}

void draw3DMapSdl(screen_t* screen, world_t *world){
  float player_fov = 1.58;

	SDL_SetRenderDrawColor(screen->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(screen->renderer);
  drawSky(screen, world);
  drawGround(screen);

	//SDL_SetRenderDrawColor(screen->renderer, 0, 200, 255, SDL_ALPHA_OPAQUE);
  	for (int r=0; r<512; r++) { 
  		float angle = world->player_a - player_fov/2 + player_fov*r/512;      
      //Pour regler la fluidité des fps, modifier l'incrementation de t, .001 => 30 fps, .002 => 60 fps, .05 => 144 fps 
  		for (float t=0; t<20; t+=.002) {
      		float cx = world->player_x + t*cos(angle);
      		float cy = world->player_y + t*sin(angle);

        	if (world->map[(int)(cy)][(int)(cx)]!=' '){
        		int line_height = HEIGHT/t;
		  		  for (int i = 0; i < 16; i++){
		  			  //SDL_RenderDrawLine(screen->renderer, r*2.5+i , (HEIGHT+line_height)/2, r*2.5+i, (HEIGHT-line_height)/2);
              SDL_Rect srcRect;
              SDL_Rect destRect;
              float arrondcx = cx - floor(cx + .5);
              float arrondcy = cy - floor(cy + .5);
              srcRect.x = arrondcx*WALL_SIZE;
              if (fabs(arrondcy) > fabs(arrondcx)) {
                  srcRect.x = arrondcy * WALL_SIZE;
              }
              srcRect.h = WALL_SIZE;
              srcRect.w = WALL_SIZE;
              destRect.x = r*2.5+i;
              destRect.y = (HEIGHT/2) - (line_height/2);
              destRect.h = line_height;
              destRect.w = 1;
              SDL_RenderCopy(screen->renderer, screen->murBriqueTexture, &srcRect, &destRect);
		  		  }
        		break;
      		}
    	}
  	}
 applyCrosshair(screen);  
 drawFPS(world, screen);

  drawMiniMap(screen, world);
  if (world->fpsView == false) {
    applyPistolet(screen);
  }else {
    applyViseeFpsPistolet(screen);
  }
  
	SDL_RenderPresent(screen->renderer);
}

void drawSky(screen_t* screen, world_t* world){
  SDL_Rect srcRect;
  SDL_Rect destRect;

  srcRect.x = world->player_a*800;
  srcRect.y = 0;
  srcRect.w = 1280;
  srcRect.h = 720/2;

  destRect.x = 0;
  destRect.y = 0;
  destRect.w = 1280;
  destRect.h = 720/2-80;

  SDL_RenderCopy(screen->renderer, screen->skyTexture, &srcRect, &destRect);
}

void drawGround(screen_t* screen){
  SDL_Rect srcRect;
  SDL_Rect destRect;
  SDL_Rect degradeDestRect;

  srcRect.x = 0;
  srcRect.y = 0; //0
  srcRect.w = FLOOR_SIZE;
  srcRect.h = FLOOR_SIZE;

  destRect.x = 0;  //0
  destRect.y = 720/2-80; //720/2-80
  destRect.w = 1280;  //1280
  destRect.h = 720-250;  //720-250

  degradeDestRect.x = 0;
  degradeDestRect.y = 720/2-80;
  degradeDestRect.w = 1280;
  degradeDestRect.h = 64;

  SDL_RenderCopy(screen->renderer, screen->groundTexture, &srcRect, &destRect);
  SDL_RenderCopy(screen->renderer, screen->degradeTexture, &srcRect, &degradeDestRect);
}


/**void draw_sprite(world_t* world, screen_t* screen) {
    for (int k = 0; k<DIFFICULTE;k++){

        float sprite_dir = atan2(world->monstre[i].y - world->player.y, world->monstre[i].x - world->player.x);
        while (sprite_dir - player.a > M_PI) {
            sprite_dir -= 2 * M_PI;
        }

        while (sprite_dir - player.a < -M_PI) sprite_dir += 2 * M_PI;

        // distance from the player to the sprite
        float sprite_dist = std::sqrt(pow(player.x - sprite.x, 2) + pow(player.y - sprite.y, 2));
        size_t sprite_screen_size = std::min(2000, static_cast<int>(fb.h / sprite_dist));
        // do not forget the 3D view takes only a half of the framebuffer, thus fb.w/2 for the screen width
        int h_offset = (sprite_dir - player.a) * (fb.w / 2) / (player.fov) + (fb.w / 2) / 2 - sprite_screen_size / 2;
        int v_offset = fb.h / 2 - sprite_screen_size / 2;

        for (size_t i = 0; i < sprite_screen_size; i++) {
            if (h_offset + int(i) < 0 || h_offset + i >= fb.w / 2) continue;
            for (size_t j = 0; j < sprite_screen_size; j++) {
                if (v_offset + int(j) < 0 || v_offset + j >= fb.h) continue;
                fb.set_pixel(fb.w / 2 + h_offset + i, v_offset + j, pack_color(0, 0, 0));
            }
        }
    }
}**/