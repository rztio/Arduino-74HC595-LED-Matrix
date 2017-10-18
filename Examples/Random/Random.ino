/*
 * A random led is chosen and increases then decreases its brightness before another one lights up and so on.   
*/

#include <LedMatrix.h>

// Set up the LedMatrix library
LedMatrix ledMatrix(A0, A1, A2, 10, 3, 3); // clock pin, latch pin, data pin, output enable pin, rows, columns

// Time in milliseconds that the led brightness changes
const int DELAY_TIME = 7;

// Stores the previous row and column number of the last led that changed
// set initially to numbers not in the matrix
int prev_row = 5;
int prev_col = 5;

void setup(){  
}

void loop() {
  // Pick a random row and column in the led matrix
  int random_row = random(0, ledMatrix.getRows());
  int random_col = random(0, ledMatrix.getCols());

  // Pick another number if the same led is chosen as last time
  if (random_row == prev_row && random_col == prev_col){
    return;
  }
 
  prev_row = random_row;
  prev_col = random_col;

  // Sets the address of th new led based on the row and column number chosen
  ledMatrix.newLed(random_row, random_col);

  // Make the led have a breathing effect
  breathe();
}

// Breathing effect increases then decreases the brightness levels of the led
void breathe() {
  ledMatrix.increaseBrightness(DELAY_TIME);
  ledMatrix.decreaseBrightness(DELAY_TIME);
}
