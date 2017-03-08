#include "SherwinToTheMAX72XX.h"
/**
Sets pin numbers and makes up device addresses. Last
device on daisy chain will be assigned address
0x01 up to however many devices connected.

PARAMETERS:
    1) Arduino pin connected to clock pin (pin 13).
    2) Arduino pin connected to data pin (pin 1).
    3) Arduino pin connected to chip select pin (pin 12).
**/
SherwinToTheMAX72XX::SherwinToTheMAX72XX(int clck, int data, int cs, int devCount){
    clckPin = clck;
    dataPin = data;
    CSPin = cs;
    deviceCount = devCount;
    bitsToWrite = deviceCount * 16;

    for(i = 0; i < deviceCount; i++){
        deviceAddress[i] = (i+1);
    }

    for(i = 0; i < bitsToWrite; i++){
        deviceData[i] = 0;
    }

}

/**
Sets designated pins to outputs. Call function
in setup().
**/
void SherwinToTheMAX72XX::setupPins(){
    pinMode(clckPin,OUTPUT);
    pinMode(dataPin,OUTPUT);
    pinMode(CSPin,OUTPUT);
    digitalWrite(CSPin,HIGH);
}

/**
Writes data from deviceData array to all
shift register
**/
void SherwinToTheMAX72XX::sendData(){
    digitalWrite(clckPin,LOW);
    digitalWrite(CSPin,LOW);

    for(i = 0; i < bitsToWrite; i++){
        digitalWrite(dataPin,deviceData[i]);
        digitalWrite(clckPin,HIGH);
        delayMicroseconds(1);
        digitalWrite(clckPin,LOW);
    }

    digitalWrite(CSPin,HIGH);
}

/**
Writes byte to buffer then writes to all
the registers.

PARAMETERS:
    1) Device address (which number device to write to)
    2) Register address to write to
    3) 1 byte data
**/
void SherwinToTheMAX72XX::writeByte(int8_t devAddress, int8_t regAddress, int8_t Byte){
    for(i = 0; i < 4; i++){
        regBits[i] = (regAddress >> i) & 1;
    }

    for(i = 0; i < 8; i++){
        dataWritten[i] = (Byte >> i) & 1;
    }

    for(i = 3, n = 4; i >= 0, n < 8; i--, n++){
        buffer[n] = regBits[i];
    }

    for(i = 7, n = 8; i >= 0, n < 16; i--, n++){
        buffer[n] = regBits[i];
    }

    startingBit = ((devAddress - 1) * 16);
    endingBit = startingBit + 16;

    for(i = startingBit,n = 0; i < endingBit, n < 16; i++, n++){
        deviceData[i] = deviceData[n];
    }

    sendData();
}

/**
Writes byte to segment pins. Bits get directly
transfered to segment pins unless decode mode
turned on.
@see writeDecodeMode()

IMPORTANT: Must call this function after writing to all
other registers. Address bits must be set to 0 so
data bits get transfered to segment pins.

PARAMETERS:
    1) Device Address (which number device to write to)
    2) 1 byte data
**/
void SherwinToTheMAX72XX::writeSegmentPins(int8_t devAddress, int8_t Byte){
    writeByte(devAddress, SEGMENT_PINS_ADDRESS, Byte);
}


/**
Digit Pins Functions:
  Each pin has its own address to write to.
  Write 1 to turn on and 0 to turn off. Pin state
  is determined by the least significant bit.

PARAMETERS:
    1) Device Address (which number device to write to)
    2) 1 byte data
**/
void SherwinToTheMAX72XX::writeDigit0Pin(int8_t devAddress, int8_t Byte){
   writeByte(devAddress, DIGIT0_ADDRESS, Byte);
}

void SherwinToTheMAX72XX::writeDigit1Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT1_ADDRESS, Byte);
}

void SherwinToTheMAX72XX::writeDigit2Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT2_ADDRESS, Byte);
}

void SherwinToTheMAX72XX::writeDigit3Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT3_ADDRESS, Byte);
}

void SherwinToTheMAX72XX::writeDigit4Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT4_ADDRESS, Byte);
}

void SherwinToTheMAX72XX::writeDigit5Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT5_ADDRESS, Byte);
}
void SherwinToTheMAX72XX::writeDigit6Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT6_ADDRESS, Byte);
}

void SherwinToTheMAX72XX::writeDigit7Pin(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DIGIT7_ADDRESS, Byte);
}

/**
Writes to decode mode register.
@see data sheet https://www.sparkfun.com/datasheets/Components/General/COM-09622-MAX7219-MAX7221.pdf

PARAMETERS:
    1) Device Address (which number device to write to)
    2) 1 byte data

NOTE:
    Possible data parameters are 0x00 for no decoding, 0x01 to decode
    digit 0, 0x0F to decode digits 0-3, and 0xFF to decode all
    digits.
**/
void SherwinToTheMAX72XX::writeDecodeMode(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DECODE_MODE_ADDRESS, Byte);
}

/**
Writes to intensity register.
@see data sheet https://www.sparkfun.com/datasheets/Components/General/COM-09622-MAX7219-MAX7221.pdf

PARAMETERS:
    1) Device address (which number device to write to)
    2) 1 byte data

NOTE:
    Possible data parameters range from 0x00 to 0x0F. Duty cycle
    length increases with each LSB sent.
**/
void SherwinToTheMAX72XX::writeIntensity(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, INTENSITY_ADDRESS, Byte);
}

/**
Writes to scan limit register.
@see data sheet https://www.sparkfun.com/datasheets/Components/General/COM-09622-MAX7219-MAX7221.pdf

PARAMETERS:
    1) Device address (which number device to write to)
    2) 1 byte data

NOTE:
    Possible data parameters are 0x00 to 0x07.0x00 displays
    digit 0 only up to 0x07 which displays all digits.
**/
void SherwinToTheMAX72XX::writeScanLimit(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, SCAN_LIMIT_ADDRESS, Byte);
}

/**
Writes to scan shut down register.
@see data sheet https://www.sparkfun.com/datasheets/Components/General/COM-09622-MAX7219-MAX7221.pdf

PARAMETERS:
    1) Device address (which number device to write to)
    2) 1 byte data

NOTE:
    Possible data parameters are 0x00 for shut down mode
    and 0x01 for normal operation.
**/
void SherwinToTheMAX72XX::writeShutdown(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, SHUTDOWN_ADDRESS, Byte);
}

/**
Writes to display test register.
@see data sheet https://www.sparkfun.com/datasheets/Components/General/COM-09622-MAX7219-MAX7221.pdf

PARAMETERS:
    1) Device address (which number device to write to)
    2) 1 byte data

NOTE:
    Possible data parameters are 0x00 for normal operation
    and 0x01 to enable display test mode.
**/
void SherwinToTheMAX72XX::writeDisplayTest(int8_t devAddress, int8_t Byte){
     writeByte(devAddress, DISPLAY_TEST_ADDRESS, Byte);
}

