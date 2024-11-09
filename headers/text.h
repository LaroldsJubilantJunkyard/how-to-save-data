#ifndef TEXT_HEADERS
#define TEXT_HEADERS

#include <gb/gb.h>

uint8_t DrawNumber(uint8_t x,uint8_t y, uint16_t number,uint8_t digits) ;
void DrawText(uint8_t column, uint8_t row, char* text);

#endif