////////////////////////////////////////////////////////////
// Source file : Bus.h
// Author : Dani
// Date : 12-03-2020
// Version : 1.0
//
// Description :
//
////////////////////////////////////////////////////////////
#ifndef V2_ROCKET_BUS_H
#define V2_ROCKET_BUS_H


class Bus {
protected:
    unsigned int bus;
    unsigned int deviceId;
    int file;
public:
     Bus(unsigned int bus, unsigned int deviceId);
    virtual ~Bus();
    virtual unsigned char * readRegisters(unsigned int length, unsigned int FromAddress);
    virtual int writeRegister(unsigned int registerAddress, unsigned char value);
    virtual int open();
    virtual void close();
};


#endif //V2_ROCKET_BUS_H
