//http://playground.arduino.cc/Code/EEPROMReadWriteLong
#include "eepromparams.h"
#include <EEPROM.h>

EEPROMParams::EEPROMParams()
{

}

EEPROMParams::EEPROMParams(int magicAddress, int magicValue)
{
    this->magicAddress = magicAddress;
    this->magicValue = magicValue;

    int savedValue = EEPROM.read(magicAddress);
    if(savedValue != magicValue) {
        //erase
        EEPROM.write(magicAddress, magicValue);
        EEPROM.write(magicAddress+1, 0);
        EEPROM.write(magicAddress+2, 0);
        EEPROM.write(magicAddress+3, 0);
        EEPROM.write(magicAddress+4, 0);
    }
}

void EEPROMParams::writeLongCounter(unsigned long value)
{
    int address = this->magicAddress+1;
    this->writeLong(address, value);
}

void EEPROMParams::writeLong(int address, unsigned long value)
{
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
}

unsigned long EEPROMParams::readLong(int address)
{
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

unsigned long EEPROMParams::readLongCounter()
{
    int address = this->magicAddress+1;
    return this->readLong(address);
}
