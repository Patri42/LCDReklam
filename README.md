
# Advertisement Display System for AVR Microcontrollers with LCD

This is an AVR microcontroller-based code written in C to display advertisements on a 16x2 LCD display. This code takes a set of clients with their messages and displays them on the LCD. The display of messages is managed in a pseudo-random manner based on a weighted system where clients with higher payments have a greater chance of their ads being displayed.

Key points of the code:

**Library Inclusions:** AVR I/O, utility for delay, standard I/O, standard library, and string handling libraries are included. Additionally, a header file for LCD control functions, lcd.h, is included.

**Structs and Variables:** The Client structure holds information related to a client, including their messages, payment, the count of messages, and the index of the last displayed message. An array clients[] is used to store multiple client instances.

**Text Scrolling Function:** lcd_scroll_text() function is used to scroll the message on the LCD screen. If the message is larger than the screen width (16 characters), the function scrolls the message from right to left.

**Main Function:** The main() function initializes the LCD screen and calculates the total payment from all clients. It then enters an infinite loop, where it continuously selects a client and a message from that client based on a pseudo-random selection process. The selected message is then displayed on the LCD screen, with each ad being displayed for a period of 1 second.

**Weighted Random Selection:** The selection of the client is based on a weighted random selection. The higher the payment by the client, the higher the chance of their message being displayed.

**Message Selection:** From the selected client, a random message is chosen for display. The code ensures that the same message is not displayed twice consecutively by comparing the new randomly selected message with the previously displayed one.

This code is designed for AVR microcontrollers and requires a connected 16x2 LCD for proper operation.

