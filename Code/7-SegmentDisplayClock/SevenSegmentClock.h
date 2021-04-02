#ifndef SevenSegmentClock_h
#define SevenSegmentClock_h

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class SevenSegment {
  public:
    SevenSegment(uint8_t i2cAdress, uint8_t segAPin, uint16_t state_A[2], uint8_t segBPin, uint16_t state_B[2], uint8_t segCPin, uint16_t state_C[2], uint8_t segDPin, uint16_t state_D[2], uint8_t segEPin,  uint16_t state_E[2], uint8_t segFPin, uint16_t state_F[2],uint8_t segGPin, uint16_t state_G[2]);//, uint8_t togglePin);
    void writeCharacter(char character);
    void initialize();

  private:
    uint8_t _PWMFrequencie = 50;
    uint8_t _togglePin;
    uint8_t _segAPin;
    uint8_t _segBPin;
    uint8_t _segCPin;
    uint8_t _segDPin;
    uint8_t _segEPin;
    uint8_t _segFPin;
    uint8_t _segGPin;
    
    uint16_t _state_A[2];
    uint16_t _state_B[2];
    uint16_t _state_C[2];
    uint16_t _state_D[2];
    uint16_t _state_E[2];
    uint16_t _state_F[2];
    uint16_t _state_G[2];
    char _character;
    uint8_t _i2cAdress;
    Adafruit_PWMServoDriver _segment;// = Adafruit_PWMServoDriver(&Wire, _i2cAdress);

    void setServo(uint8_t segmentNumber, uint16_t values[2], bool state);

};


#endif
