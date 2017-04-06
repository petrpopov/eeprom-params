#ifndef eepromparams_h
#define eepromparams_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class EEPROMParams
{
    public:
        EEPROMParams();
        EEPROMParams(int magicAddress, int magicValue);
        int magicAddress;
        int magicValue;
        void writeLongCounter(unsigned long value);
        void writeLong(int address, unsigned long value);
        unsigned long readLong(int address);
        unsigned long readLongCounter();
};

#endif
