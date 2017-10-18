#include <LedMatrix.h>

LedMatrix ledMatrix(A0, A1, A2, 10, 3, 3);

void loop(){
  for(int r = 0; r < ledMatrix.getRows(); r ++){
    for(int c = 0; c < ledMatrix.getCols(); c++){
       ledMatrix.newLed(r, c);
       ledMatrix.setLeds(500);
    }
  }  
}

