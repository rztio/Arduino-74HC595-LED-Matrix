/*
 * A random dice pattern is displayed when 'r' and 'ENTER' used in the arduino serial monitor.  
*/

#include <LedMatrix.h>

// Set up the LedMatrix library
LedMatrix ledMatrix(A0, A1, A2, 10, 3, 3); // clock pin, latch pin, data pin, output enable pin, rows, columns

// LED addresses
byte row1_col1 = B10000111;
byte row1_col2 = B01000111;
byte row1_col3 = B00100111;

byte row2_col1 = B00100111;
byte row2_col2 = B01001011;
byte row2_col3 = B00101011;

byte row3_col1 = B10001101;
byte row3_col2 = B01001101;
byte row3_col3 = B00101101;

// Dice patterns
byte one[]   = {row2_col2};
byte two[]   = {row1_col1, row3_col3};
byte three[] = {row1_col3, row2_col2, row3_col1};
byte four[]  = {row1_col1, row1_col3, row3_col1, row3_col3};
byte five[]  = {row1_col1, row1_col3, row3_col1, row3_col3, row2_col2};
byte six[]   = {row1_col1, row1_col2, row1_col3, row3_col1, row3_col2, row3_col3};

// Array of dice patterns 
byte* dice[] = {one, two, three, four, five, six};

// Amount of times dice numbers changes
const int SHUFFLE = 5;

const int INTERVAL = 150; // Time between dice dice numbers changing in milliseconds
const int DELAY_TIME = 2; // Time between individual leds lighting up to make up a dice pattern in milliseconds
                          // short time used to give the effect that they are on at the same time
           
unsigned long previous_time = 0; // Keep track of when the dice number last changed 
int random_dice_number;  // Stores dice number

// Bools for setting up loops
bool showDice = false;      
bool newShuffle = false;

void setup() {
  // Set up serial communications
  Serial.begin(9600);
}

void loop() {
  // Takes input at the start
  input();

  // Takes input and keeps leds on 
  while(showDice){
     setDice();
     input();      
  }         
}

// Input through serial communication
void input(){
  if (Serial.available() > 0) { // Check there are serial to the serial
    if (Serial.read() == 114){  // When character 'r' which has ASCII code of 114 is read, roll the dice 
      rollDice();
      showDice = true; 
      
      // Display the dice number through serial
      Serial.print("Dice Number = ");
      Serial.print(random_dice_number);
      Serial.print('\n');      
    } 
  }
}

// Changes the dice number for one roll of the dice
void rollDice(){
 for(int i = 0; i < SHUFFLE; i++) {   // Shuffle the dice a number of times    
   random_dice_number = random(1, 7); // Get a random number from 1 - 6
     
   newShuffle = true;

   // Keeps displaying the same dice pattern if the time elasped since the 
   // previous pattern is less than a set amount of time
   while(newShuffle){ 
    if(millis() - previous_time < INTERVAL){  
      setDice();
    } else {
      previous_time = millis();
      newShuffle = false;
    }
   }
 }
}

// Retrieves dice pattern to display on the leds
void setDice() {
 byte* diceNumber = dice[random_dice_number - 1];

 // Each led is displayed one at a time in the dice pattern 
 for (int i = 0; i < random_dice_number; i++) {
   ledMatrix.setLedData(diceNumber[i]); // The led address to be sent to the 74hc595
   ledMatrix.setLeds(); // Turn the led on   
   delay(DELAY_TIME); // Wait before changing to te next led  
 }  
}
