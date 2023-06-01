#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>

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
	lcd_enable_blinking();
	lcd_enable_cursor();
	lcd_puts("Skriv in koden:");

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
		lcd_set_cursor(0,1);
		lcd_puts(client.messages[message_index]);

		// Wait for 20 seconds before displaying the next ad.
		_delay_ms(20000);
	}

	return 0;
}