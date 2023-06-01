#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)
// https://wokwi.com/projects/363784064760337409



typedef struct 
{
  char *messages[3];
  int payment;
  int messageCount;
  int lastDisplayed;
} Client ;


Client clients[] = {
	{
		{"Kop bil hos Harry", "En god bilaffar (for Harry!)", "Hederlige Harrys Bilar"},
		5000,
		3,
		-1
	},
	{
		{"Mysterier? Ring Långben", "Långben fixar biffen"},
		4000,
		2,
		-1
	},
	{
		{"Köp paj hos Farmor Anka", "Skynda innan Mårten ätit alla pajer"},
		3000,
		2,
		-1
	},
	{
		{"Låt Petter bygga åt dig", "Bygga svart? Ring Petter"},
		1500,
		2,
		-1
	},
	{
		{"Synas här? IOT:s Reklambyrå"},
		1000,
		1,
		-1
	}
};

int main(void)
{
  lcd_init();

  // start loop with commercial 



  lcd_enable_blinking();
  lcd_enable_cursor();
  lcd_puts("Skriv in koden:");

    int num = 0;
   while(1) {
        _delay_ms(3000);
        num++;
        lcd_set_cursor(0,1);
        lcd_printf("Waiting: %d", num);
   }
	return 0;
}