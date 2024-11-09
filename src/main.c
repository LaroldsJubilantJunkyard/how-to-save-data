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
#include "coin.h"
#include "saved_data.h"



uint8_t HasExistingSave(void){

    uint8_t saveDataExists = FALSE;
    
    ENABLE_RAM;

    saveDataExists = savedCheckFlag1==12345;

    DISABLE_RAM;

    return saveDataExists;
}

void InitializeGameData(void){

    playerX=80<<4;
    playerY=72<<2;

    coinCount=0;
    RandomlyRePositionCoin();

    ENABLE_RAM;
    savedCoinCount=0;
    savedCheckFlag1=12345;
    savedPlayerX=playerX;
    savedPlayerY=playerY;
    savedCoinX=coinX;
    savedCoinY=coinY;
    DISABLE_RAM;

}

void LoadSaveData(void){
    
     ENABLE_RAM;

    playerX = savedPlayerX;
    playerY = savedPlayerY;
    coinX = savedCoinX;
    coinY = savedCoinY;
    coinCount = savedCoinCount;

    DISABLE_RAM;
}

void SaveData(void){

    ENABLE_RAM;

    savedCoinCount=coinCount;
    savedCheckFlag1=12345;
    savedPlayerX=playerX;
    savedPlayerY=playerY;
    savedCoinX=coinX;
    savedCoinY=coinY;

    DISABLE_RAM;
}

void main(void)
{
    DISPLAY_ON;

    SHOW_BKG;
    SHOW_SPRITES;
    SPRITES_8x16;

    set_sprite_data(0,PlayerSprite_TILE_COUNT,PlayerSprite_tiles);
    set_sprite_data(PlayerSprite_TILE_COUNT,CoinSprite_TILE_COUNT,CoinSprite_tiles);

    set_bkg_data(0,Font_TILE_COUNT,Font_tiles);
    set_bkg_data(Font_TILE_COUNT,GBDKSaveExampleBackground_TILE_COUNT,GBDKSaveExampleBackground_tiles);

    set_bkg_based_tiles(0,0,20,18,GBDKSaveExampleBackground_map,Font_TILE_COUNT);

    initrand(DIV_REG);

    if(HasExistingSave()){

        LoadSaveData();

    }else{

        InitializeGameData();
    }

    DrawCoinCount();


    // Loop forever
    while(1) {

        UpdatePlayer();

        // Update the coin, this function returns if the player & coin are colliding
        // Check if the player is colliding with the coin
        if(UpdateCoin()){

            // increase the count, and update the user interface
            coinCount++;
            DrawCoinCount();

            // Re position the coin
            RandomlyRePositionCoin();

            // Save the data
            SaveData();
        }

		// Done processing, yield CPU and wait for start of next frame
        vsync();
    }
}
