#include <iostream>
#include "abstractio.h"

class ConsoleInput : public InputDevice
{
public:
    int read() override
    {
        int value;
        std::cin >> value;
        return value;
    }
};

class ConsoleOutput : public OutputDevice
{
public:
    void write(std::string value) override
    {
        std::cout << value << std::endl;
    }

    void write(int value) override
    {
        std::cout << value << std::endl;
    }

    void write(char value) override
    {
        std::cout << value << std::endl;
    }
};