#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include "common.h"
#include "PlayerSprite.h"


#define PLAYER_MOVE_SPEED 13
int16_t playerX, playerY;

uint8_t joypadCurrent=0, joypadPrevious=0; 

void UpdatePlayer(void){

    joypadPrevious = joypadCurrent;
    joypadCurrent = joypad();

    if(joypadCurrent & J_UP){
        playerY-=PLAYER_MOVE_SPEED;
    }else if(joypadCurrent & J_DOWN){
        playerY+=PLAYER_MOVE_SPEED;
    }

    if(joypadCurrent & J_LEFT){
        playerX-=PLAYER_MOVE_SPEED;
    }else if(joypadCurrent & J_RIGHT){
        playerX+=PLAYER_MOVE_SPEED;
    }
    
    if((playerX>>4)<(AREA_LEFT+8))playerX=(AREA_LEFT+8)<<4;
    if((playerX>>4)>(AREA_RIGHT-8))playerX=(AREA_RIGHT-8)<<4;

    if((playerY>>4)<(AREA_TOP+8))playerY=(AREA_TOP+8)<<4;
    if((playerY>>4)>(AREA_BOTTOM-8))playerY=(AREA_BOTTOM-8)<<4;
        
    move_metasprite_ex(PlayerSprite_metasprites[0],0,0,0,(playerX>>4)+8,(playerY>>4)+16);
}