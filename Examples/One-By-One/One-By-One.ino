/*
 * Lights up the next led in the matrix one at a time. 
*/

#include <LedMatrix.h>

// Set up the LedMatrix library
LedMatrix ledMatrix(A0, A1, A2, 10, 3, 3); // clock pin, latch pin, data pin, output enable pin, rows, columns

// Time in milliseconds before the led changes   
const int DELAY_TIME = 500;

void setup(){
}

void loop(){
  for(int r = 0; r < ledMatrix.getRows(); r ++){
    for(int c = 0; c < ledMatrix.getCols(); c++){
       ledMatrix.newLed(r, c);  // Set the address of the led that will light up
       ledMatrix.setLeds();     // Turn the led on 
	     delay(DELAY_TIME);       // Wait before changing to the next led
    }
  }  
}

