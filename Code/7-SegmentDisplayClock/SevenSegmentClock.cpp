#include "Arduino.h"
#include "SevenSegmentClock.h"

#define ON 1
#define OFF 0

SevenSegment::SevenSegment(uint8_t i2cAdress, uint8_t segAPin, uint16_t state_A[2], uint8_t segBPin, uint16_t state_B[2], uint8_t segCPin, uint16_t state_C[2], uint8_t segDPin, uint16_t state_D[2], uint8_t segEPin,  uint16_t state_E[2], uint8_t segFPin, uint16_t state_F[2], uint8_t segGPin, uint16_t state_G[2]){ //, uint8_t togglePin) {
  _segAPin = segAPin;
  _segBPin = segBPin;
  _segCPin = segCPin;
  _segDPin = segDPin;
  _segEPin = segEPin;
  _segFPin = segFPin;
  _segGPin = segGPin;

  _state_A[0] = state_A[0];
  _state_A[1] = state_A[1];
  _state_B[0] = state_B[0];
  _state_B[1] = state_B[1];
  _state_C[0] = state_C[0];
  _state_C[1] = state_C[1];
  _state_D[0] = state_D[0];
  _state_D[1] = state_D[1];
  _state_E[0] = state_E[0];
  _state_E[1] = state_E[1];
  _state_F[0] = state_F[0];
  _state_F[1] = state_F[1];
  _state_G[0] = state_G[0];
  _state_G[1] = state_G[1];
  _i2cAdress = i2cAdress;
}

void SevenSegment::initialize() {
  _segment = Adafruit_PWMServoDriver(&Wire, _i2cAdress);
  _segment.begin();
  _segment.setPWMFreq(_PWMFrequencie);
  //Wire.setClock(400000);
}

void SevenSegment::setServo(uint8_t segmentNumber, uint16_t values[2], bool state) {
  _segment.setPWM(segmentNumber, 0, values[state]);
}

void SevenSegment::writeCharacter(char character) {
  _character = character;
  switch (_character) {
    //Numbers
    case '0':
    case 'O':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);
      break;

    case '1':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, OFF);
      break;

    case '2':
    case 'Z':
    case 'z':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case '3':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);

      break;
    case '4':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;
    case '5':
    case 'S':
    case 's':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);

      break;
    case '6':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);

      break;
    case '7':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, OFF);
      break;
    case '8':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;
    case '9':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    //Letters

    case 'A':
    case 'a':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'B':
    case 'b':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'C':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);

      break;

    case 'c':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'D':
    case 'd':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'E':
    case 'e':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'F':
    case 'f':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);

      break;

    case 'G':
    case 'g':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);
      break;

    case 'H':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'h':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'I':
    case 'i':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);
      break;

    case 'J':
    case 'j':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, OFF);
      break;

    case 'L':
    case 'l':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);
      break;

    case 'N':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);
      break;

    case 'n':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'o':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'P':
    case 'p':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'Q':
    case 'q':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'R':
    case 'r':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'T':
    case 't':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case 'U':
    case 'u':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, ON);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, OFF);
      break;

    case 'Y':
    case 'y':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, ON);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    //Special Characters
    case '-':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

    case '*':
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, ON);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, ON);
      setServo(_segGPin, _state_G, ON);
      break;

    case ' ':
      setServo(_segAPin, _state_A, OFF);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, OFF);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, OFF);
      break;

    default:
      //Non existing character!
      setServo(_segAPin, _state_A, ON);
      setServo(_segBPin, _state_B, OFF);
      setServo(_segCPin, _state_C, OFF);
      setServo(_segDPin, _state_D, ON);
      setServo(_segEPin, _state_E, OFF);
      setServo(_segFPin, _state_F, OFF);
      setServo(_segGPin, _state_G, ON);
      break;

  }
}
