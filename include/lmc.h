#pragma once
#ifndef LMC_H
#define LMC_H

#include <array>
#include <vector>
#include <string>
#include <iostream>

const int MEMORY_SIZE = 100;
const std::string FILEPATH = "../programs/ascii_table.lmc";

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
    bool isDebug = true;

    int fetch();
    void decode(int v);
    void execute();
    void step();
    void main();
    void reset();
    std::array<int, MEMORY_SIZE> getMemory();
    void setMemory(std::vector<int> m);
    void printMemory();
    void save();
    void load();
    void printRegistries();
    void printStatus();
};

#endif // LMC_H
