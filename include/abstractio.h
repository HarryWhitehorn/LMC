#pragma once
#ifndef ABSTRACTIO_H
#define ABSTRACTIO_H

class InputDevice
{
public:
    virtual int read() = 0;
    virtual ~InputDevice() = default;
};

class OutputDevice
{
public:
    virtual void write(std::string value) = 0;
    virtual void write(int value) = 0;
    virtual void write(char value) = 0;
    virtual ~OutputDevice() = default;
};

#endif // ABSTRACTIO_H