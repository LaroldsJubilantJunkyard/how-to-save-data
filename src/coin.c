#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>
#include <rand.h>
#include "CoinSprite.h"
#include "PlayerSprite.h"
#include "GBDKSaveExampleBackground.h"
#include "Font.h"
#include "text.h"
#include "player.h"
#include "common.h"
#include "hud.h"

int16_t coinX, coinY;
uint8_t coinCount;

uint8_t IsPlayerCollidingWithCoin(void){

    int16_t playerCoinDX = (playerX>>4)-coinX;
    int16_t playerCoinDY = (playerY>>4)-coinY;

    int16_t distanceSquared = playerCoinDX*playerCoinDX + playerCoinDY*playerCoinDY;

    return distanceSquared<144;
}

void RandomlyRePositionCoin(void){

    do{
        
        // Randomly re-position the coin
        // We wrap this in a do-while loop, so the player can't collect
        // Two coins if the new position is already overlapping the player
        coinX = (rand()%(AREA_RIGHT-AREA_LEFT-8))+AREA_LEFT+4;
        coinY = (rand()%(AREA_BOTTOM-AREA_TOP-8))+AREA_TOP+4;

    }while(IsPlayerCollidingWithCoin());
}

void DrawCoin(void){
    
    move_metasprite_ex(CoinSprite_metasprites[0],PlayerSprite_TILE_COUNT,0,2,coinX+8,coinY+16);

}