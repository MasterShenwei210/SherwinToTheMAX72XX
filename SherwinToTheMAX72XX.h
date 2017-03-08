/**
Library works for MAX7219 and MAX7221.
See cpp file for functions instructions.
**/
#ifndef SHERWINTOTHEMAX72XX_H
#define SHERWINTOTHEMAX72XX_H

#include "Arduino.h"

#define SEGMENT_PINS_ADDRESS    0X00    //send data to No-OP to either bypass to seg pins or through decode-mode (BCD code B)
#define DIGIT0_ADDRESS          0X01
#define DIGIT1_ADDRESS          0X02
#define DIGIT2_ADDRESS          0X03
#define DIGIT3_ADDRESS          0X04
#define DIGIT4_ADDRESS          0X05
#define DIGIT5_ADDRESS          0X06
#define DIGIT6_ADDRESS          0X07
#define DIGIT7_ADDRESS          0X08
#define DECODE_MODE_ADDRESS     0X09
#define INTENSITY_ADDRESS       0X0A
#define SCAN_LIMIT_ADDRESS      0X0B
#define SHUTDOWN_ADDRESS        0X0C
#define DISPLAY_TEST_ADDRESS    0X0F
/**
IMPORTANT:
    The device address parameters are not an official
    address. They have been made up in the constructor
    so devices that are daisy chained can be written to
    individually. Addresses start off as 0x01 up to
    however many devices are daisy chained (max 100).
**/
class SherwinToTheMAX72XX
{
    private:
        void sendData();
        void writeByte(int8_t devAddress, int8_t regAddress, int8_t Byte);

        int8_t Byte;
        int clck, data, cs, devCount;
        int clckPin,dataPin,CSPin   ;
        int devAddress,regAddress;
        int deviceCount;
        int bitsToWrite;

        bool deviceData[1600];
        int i,n;
        bool regBits[4];
        bool dataWritten[8];
        int startingBit,endingBit;
        bool buffer[16];

    public:
        SherwinToTheMAX72XX(int clck, int data, int cs, int devCount);
        void setupPins();

        void writeSegmentPins(int8_t devAddress, int8_t Byte);
        void writeDigit0Pin(int8_t devAddress, int8_t Byte);
        void writeDigit1Pin(int8_t devAddress, int8_t Byte);
        void writeDigit2Pin(int8_t devAddress, int8_t Byte);
        void writeDigit3Pin(int8_t devAddress, int8_t Byte);
        void writeDigit4Pin(int8_t devAddress, int8_t Byte);
        void writeDigit5Pin(int8_t devAddress, int8_t Byte);
        void writeDigit6Pin(int8_t devAddress, int8_t Byte);
        void writeDigit7Pin(int8_t devAddress, int8_t Byte);
        void writeDecodeMode(int8_t devAddress, int8_t Byte);
        void writeIntensity(int8_t devAddress, int8_t Byte);
        void writeScanLimit(int8_t devAddress, int8_t Byte);
        void writeShutdown(int8_t devAddress, int8_t Byte);
        void writeDisplayTest(int8_t devAddress, int8_t Byte);

        int deviceAddress[100];

};

#endif // SHERWINTOTHEMAX72XX_H
