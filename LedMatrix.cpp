#include "Arduino.h"
#include "LedMatrix.h"

LedMatrix::LedMatrix(int clockPin, int latchPin, int dataPin, int outputEnablePin, int rows, int cols){
	_clockPin = clockPin;
	_latchPin = latchPin,
	_dataPin = dataPin;
	_outputEnablePin = outputEnablePin;
	_rows = rows;
	_cols = cols;
		
	pinMode(_clockPin , OUTPUT);
	pinMode(_latchPin, OUTPUT);
	pinMode(_dataPin, OUTPUT);  
	pinMode(_outputEnablePin, OUTPUT);  
}

int LedMatrix::getRows(){
	return _rows;
}

int LedMatrix::getCols(){
	return _cols;
}

byte LedMatrix::getLedData(){
	return _ledData;
}

void  LedMatrix::setLedData(byte newLedData){
	_ledData = newLedData;
}

void LedMatrix::newLed(int row, int col){
	byte new_col = (B10000000 >> col);
	byte new_row = (B00001111 & ~(B0001000 >> row));  
	_ledData = new_col | new_row;
}

void LedMatrix::setLeds(){
  digitalWrite(_latchPin, LOW);
  shiftOut(_dataPin, _clockPin, LSBFIRST,_ledData);
  digitalWrite(_latchPin, HIGH);
}

void LedMatrix::increaseBrightness(int delay_time){
	for (byte b = 255; b > 0; b--){
		setBrightness(b);
		setLeds();
		delay(delay_time);
	}
}

void LedMatrix::decreaseBrightness(int delay_time){
    for (byte b = 0; b < 255; b++) {
      setBrightness(b);
	  setLeds();
	  delay(delay_time);
	}
}

void LedMatrix::setBrightness(byte brightness){
	analogWrite(_outputEnablePin, brightness);
}