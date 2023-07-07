#include <windows.h>
#include <exception>
#include "DeviceDriver.h"

#define TRY_CNT 5

class ReadFailException : public std::exception
{

};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int value = (m_hardware->read(address));
    for(int i=1; i< TRY_CNT; ++i)
    {
        Sleep(200);
        if (value != (m_hardware->read(address))) throw ReadFailException();
    }

    return value;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}