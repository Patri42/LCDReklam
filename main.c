#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcd.h"

// #define BIT_SET(a, b) ((a) |= (1ULL << (b)))
// #define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
// #define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
// #define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

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
		{"Mysterier? Ring Langben", "Langben fixar biffen"},
		4000,
		2,
		-1
	},
	{
		{"Kop paj hos Farmor Anka", "Skynda innan Marten atit alla pajer"},
		3000,
		2,
		-1
	},
	{
		{"Lat Petter bygga at dig", "Bygga svart? Ring Petter"},
		1500,
		2,
		-1
	},
	{
		{"Synas har? IOT:s Reklambyra"},
		1000,
		1,
		-1
	}
};

void lcd_scroll_text(char* message, int delay_time) {
    int length = strlen(message);
  
    if(length <= 16) {
        lcd_set_cursor(0, 0);
        lcd_puts(message);
        for(int i = 0; i < delay_time; i++)
            _delay_ms(1);
        return;
    }
  
    for(int i = 0; i < length - 15; i++) {
        char buffer[17];
        memcpy(buffer, &message[i], 16);
        buffer[16] = '\0';
        lcd_set_cursor(0, 0);
        lcd_puts(buffer);
        for(int j = 0; j < delay_time; j++)
            _delay_ms(1);
    }
}

int main(void)
{
	lcd_init();
	//lcd_enable_blinking();
	//lcd_enable_cursor();
	//lcd_puts("Skriv in koden:");

	int total_payment = 0;
	for (int i = 0; i < sizeof(clients) / sizeof(Client); i++) {
		total_payment += clients[i].payment;
	}

	while(1) {
		// Choose a client based on the weighted random selection.
		int payment_sum = 0;
		int random_payment = rand() % total_payment;
		int client_index = -1;
		for (int i = 0; i < sizeof(clients) / sizeof(Client); i++) {
			payment_sum += clients[i].payment;
		if (payment_sum > random_payment) {
			client_index = i;
			break;
		}
		}

		// Choose a message from the client.
		Client client = clients[client_index];
		int message_index = rand() % client.messageCount;
		if (message_index == client.lastDisplayed) {
			message_index = (message_index + 1) % client.messageCount;
		}
		client.lastDisplayed = message_index;

		// Display the message.
		lcd_set_cursor(0,0);
		lcd_scroll_text(clients[client_index].messages[message_index], 300);

		// Wait for 1 second before displaying the next ad.
		_delay_ms(1000);
	}

	return 0;
}