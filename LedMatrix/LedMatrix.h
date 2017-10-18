#ifndef LedMatrix_h
#define LedMatrix_h

#include "Arduino.h"

class LedMatrix {
	public:
		LedMatrix(int clockPin, int latchPin, int dataPin, int outputEnablePin, int rows, int cols);
		int getRows();
		int getCols();
		byte getLedData();
		void  setLedData(byte newLedData);
		void newLed(int row, int col);
		void setLeds();
		void increaseBrightness(int delay_time);
		void decreaseBrightness(int delay_time);
		void setBrightness(byte brightness);
	private:
		int _clockPin;
		int _latchPin;
		int _dataPin;
		int _outputEnablePin;
		int _rows;
		int _cols;
		byte _ledData;
};

#endif
