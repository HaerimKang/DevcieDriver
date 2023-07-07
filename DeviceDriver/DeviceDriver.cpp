#include <exception>
#include "DeviceDriver.h"

class WriteFailException : public std::exception
{

};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    return (int)(m_hardware->read(address));
}

void DeviceDriver::write(long address, int data)
{
    if (m_hardware->read(address) != 0xFF) throw WriteFailException();

    m_hardware->write(address, (unsigned char)data);
}