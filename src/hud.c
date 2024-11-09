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
#include "coin.h"
#include "common.h"

void DrawCoinCount(void){

    fill_bkg_rect(1,16,12,1,0);

    if(coinCount==0){
        DrawText(1,16,"No coins");
    }else {
        DrawNumber(1,16,coinCount,3);
        if(coinCount==1)DrawText(5,16,"coin");
        else DrawText(5,16,"coins");
    }
}
