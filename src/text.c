#include <gb/gb.h>
#include <stdint.h>
#include "Font.h"
uint8_t GetCharacterVRamTile(char character) {

    uint8_t vramTile=0;


    // Char's can be interpreted as integers
    // We don't need to map every alpha-numeric character
    // We can use basic math to simplify A-Z and 0-9
    if(character >='a'&&character <= 'z')vramTile = (character-'a')+1;
    else if(character >= 'A'&&character <= 'Z')vramTile = (character-'A')+1;
    else if(character >= '0'&&character <= '9')vramTile = (character-'0')+27;
    else {
        switch(character) {
            case '!': vramTile = 37; break;
            case ':': vramTile = 38; break;
            case '?': vramTile = 39; break;
            case '/': vramTile = 40; break;
            case '=': vramTile = 41; break;
            case ',': vramTile = 42; break;
            case '.': vramTile = 43; break;
            case '<': vramTile = 44; break;
            case '>': vramTile = 45; break;
        }
    }

    return vramTile;

}

void DrawText(uint8_t column, uint8_t row, char* text){

    // Get the address of the first tile in the row
    uint8_t* vramAddress = get_bkg_xy_addr(column,row);

    uint16_t index=0;

    while(text[index]!='\0'){

        char character = text[index];

        // Draw our character at the address
        // THEN, increment the address
        uint8_t vramTile = GetCharacterVRamTile(character);

        set_vram_byte(vramAddress++,vramTile);

        index++;

    }
}



uint8_t DrawNumber(uint8_t x,uint8_t y, uint16_t number,uint8_t digits) {

    uint16_t pow10 = 10000;

    for(uint8_t i=5;i>0;i--){
        
        if(digits>=i){
            if(number>=pow10)set_bkg_tile_xy(x++,y,(number/pow10)%10+27);
            else set_bkg_tile_xy(x++,y,27);
        }

        pow10/=10;
    }

    return x;
}
