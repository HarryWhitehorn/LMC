#pragma once
#ifndef LMC_H
#define LMC_H

#include <array>
#include <vector>
#include <string>
#include "abstractio.h"

const int MEMORY_SIZE = 100;
const std::string FILEPATH = "c:\\Users\\harry\\Documents\\GitHub\\LMC\\programs\\ascii.lmc";

enum Opcode
{
    ADD = 1,   // Add
    SUB = 2,   // Subtract
    STA = 3,   // Store
    LDA = 5,   // Load
    BRA = 6,   // Branch Always
    BRZ = 7,   // Branch if Zero
    BRP = 8,   // Branch if positive
    IO = 9,    // Input / Output
    INP = 901, // Input
    OUT = 902, // Output
    OTC = 922, // Output Character
    HLT = 0,   // Halt
    // DAT = 999 // Data
};

class Lmc
{
private:
    std::array<int, MEMORY_SIZE> memory = {0};
    int pc = 0;  // Program Counter
    int ir = 0;  // Instruction Register
    int ar = 0;  // Address Register
    int acc = 0; // Accumulator
    InputDevice *inputDevice;
    OutputDevice *outputDevice;
    bool isRunning = true;

    void add();
    void sub();
    void sta();
    void lda();
    void bra();
    void brz();
    void brp();
    void inp();
    void out();
    void otc();
    void hlt();
    void hlt(std::string errorMsg);

public:
    bool isDebug = false;

    Lmc(InputDevice *input, OutputDevice *output, bool debug = false);
    // Lmc(bool debug = false);
    ~Lmc();

    int fetch();
    void decode(int v);
    void execute();
    void step();
    void main();
    void reset();
    void setMemory(std::vector<int> m);
    void printMemory();
    void save(std::string path=FILEPATH);
    void load(std::string path=FILEPATH);
    void printRegistries();
    void printStatus();

    int getPc();
    int getAcc();
    int getIr();
    int getAr();
    std::array<int, MEMORY_SIZE> getMemory();
    bool getIsRunning();

    void setInput(InputDevice *input);
    void setOuput(OutputDevice *output);
};

#endif // LMC_H
