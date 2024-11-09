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

    /**
     * @brief Check for a specific value on the 'savedCheckFlag1' variable. RAM variables (on cartridge or on the handheld), will
     * always have SOME sort of value. If no save file exists, all the FRAM/SRAM variables will have random values. When we save the game
     * we'll set the 'savedCheckFlag1' variable to a very specific value. This let's us know later, that we have a valid save file.
     * 
     */
    saveDataExists = savedCheckFlag1==12345;

    DISABLE_RAM;

    return saveDataExists;
}

void InitializeGameData(void){

    playerX=80<<4;
    playerY=72<<2;

    coinCount=0;
    RandomlyRePositionCoin();

}

void LoadSaveData(void){
    
    ENABLE_RAM;

    /**
     * @brief Copy values from the cartridge's FRAM/SRAM into the normal on-device RAM
     */
    playerX = savedPlayerX;
    playerY = savedPlayerY;
    coinX = savedCoinX;
    coinY = savedCoinY;
    coinCount = savedCoinCount;

    DISABLE_RAM;
}

void SaveData(void){

    ENABLE_RAM;


    /**
     * @brief Copy values from the normal on-device RAM to the cartridge's FRAM/SRAM. We make sure
     * to set the savedCheckFlag1 variable, so we know that valid data exists. 
     */
    savedCheckFlag1=12345;
    savedPlayerX=playerX;
    savedPlayerY=playerY;
    savedCoinX=coinX;
    savedCoinY=coinY;
    savedCoinCount=coinCount;

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


    /**
     * @brief We'll check if we already have save data. If we do, we'll load that into normal RAM. 
     * If we don't already have data, we'll initialize our game data and save it.
     */
    if(HasExistingSave()){
        LoadSaveData();
    }else{
        InitializeGameData();
        SaveData();
    }

    /**
     * @brief After we've initalized or loaded data, we can draw how many coins we have.
     */
    DrawCoinCount();


    // Loop forever
    while(1) {

        UpdatePlayer();
        DrawCoin();

        if(IsPlayerCollidingWithCoin()){

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
