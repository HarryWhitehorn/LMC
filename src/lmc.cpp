#include <fstream>
#include <iostream>
#include <vector>
#include "lmc.h"
#include "utils.h"
#include "consoleio.cpp"

// using namespace std;

void Lmc::add()
{
    acc += memory[ar];
}
void Lmc::sub()
{
    acc -= memory[ar];
}
void Lmc::sta()
{
    memory[ar] = acc;
}
void Lmc::lda()
{
    acc = memory[ar];
}
void Lmc::bra()
{
    pc = ar;
}
void Lmc::brz()
{
    if (acc == 0)
    {
        pc = ar;
    }
}
void Lmc::brp()
{
    if (acc >= 0)
    {
        pc = ar;
    }
}

void Lmc::inp()
{
    // take user input and store in acc
    // cin >> acc;
    acc = inputDevice->read();
}
void Lmc::out()
{
    // print acc
    // cout << acc << endl;
    outputDevice->write(acc);
}
void Lmc::otc()
{
    // print acc as ascii
    // cout << (char)acc << endl;
    outputDevice->write(char(acc));
}
void Lmc::hlt()
{
    isRunning = false;
}
void Lmc::hlt(std::string errorMsg)
{
    // cout << errorMsg << endl; // TODO: int codes?
    outputDevice->write(errorMsg);
    hlt();
}

Lmc::Lmc(InputDevice *input, OutputDevice *output, bool debug) : inputDevice(input), outputDevice(output), isDebug(debug)
{
}

// Lmc::Lmc(bool debug)
// {

// }

Lmc::~Lmc() {}

int Lmc::fetch()
{
    int v = memory[pc];
    pc++;
    return v;
}

void Lmc::decode(int v)
{
    ir = v / 100;
    ar = v % 100;
}

void Lmc::execute()
{
    switch (ir)
    {
    case ADD:
        add();
        break;
    case SUB:
        sub();
        break;
    case STA:
        sta();
        break;
    case LDA:
        lda();
        break;
    case BRA:
        bra();
        break;
    case BRZ:
        brz();
        break;
    case BRP:
        brp();
        break;
    case IO:
        switch (ir * 100 + ar)
        {
        case INP:
            inp();
            break;
        case OUT:
            out();
            break;
        case OTC:
            otc();
            break;
        default:
            // cout << "Unknown instruction: " << ir << ". With address: " << ar << endl;
            break;
        }
        break;
    case HLT:
        hlt();
        break;
    default:
        // cout << "unknown instruction: " << ir << endl;
        break;
    }
}

void Lmc::step()
{
    int v = fetch();
    decode(v);
    execute();
}

void Lmc::main()
{
    isRunning = true;
    while (isRunning)
    {
        if (isDebug)
        {
            // cout << endl;
            printStatus();
        }
        step();
    }
}

void Lmc::reset()
{
    std::fill(begin(memory), end(memory), 0);
    acc = 0;
    pc = 0;
    ir = 0;
    ar = 0;
    isRunning = true;
}

std::array<int, 100> Lmc::getMemory()
{
    return memory;
}

void Lmc::setMemory(std::vector<int> m)
{
    for (int i = 0; i < size(m); ++i)
    {
        memory[i] = m[i];
    }
}

void Lmc::printMemory()
{
    for (int i = 0; i < size(memory); ++i)
    {
        if (i % 10 == 0 && i != 0)
        {
            // cout << endl;
        }
        // cout << zfill(memory[i]) << ", ";
    }
    // cout << endl;
}

void Lmc::save(std::string path)
{
    std::ofstream file(path);
    file.close();
}

void Lmc::load(std::string path)
{
    std::ifstream file(path);
    if (isDebug)
    {
        // cout << "Loading from " << FILEPATH << endl;
    }
    std::string fileBuffer;
    std::vector<int> m;
    int i = 0;
    while (getline(file, fileBuffer))
    {
        try
        {
            int buffer = stoi(fileBuffer);
            m.push_back(buffer);
            i++;
        }
        catch (const std::invalid_argument &ia)
        {
            if (isDebug)
            {
                // cout << "Skipping line: " << fileBuffer << endl;
            }
        }
    }
    file.close();
    reset();
    setMemory(m);
}

void Lmc::printRegistries()
{
    // cout << "PC: " << pc << ". IR: " << ir << ". AR: " << ar << ". ACC: " << acc << "." << endl;
}

void Lmc::printStatus()
{
    printRegistries();
    printMemory();
}

int Lmc::getPc()
{
    return pc;
}

int Lmc::getAcc()
{
    return acc;
}

int Lmc::getIr()
{
    return ir;
}

int Lmc::getAr()
{
    return ar;
}

bool Lmc::getIsRunning()
{
    return isRunning;
}

void Lmc::setIsRunning(bool running)
{
    isRunning = running;
}

void Lmc::setInput(InputDevice *input)
{
    inputDevice = input;
}

void Lmc::setOuput(OutputDevice *output)
{
    outputDevice = output;
}

// TODO
// - Compile from Assembly to dec.2
// - Add saving to file
// - Create UI using qt.
// - Comment
// - readme.md
// - publish

// int main()
// {
//     // cout << "START" << endl;
//     InputDevice *in = new ConsoleInput();
//     OutputDevice *out = new ConsoleOutput();
//     Lmc l(in, out);
//     l.isDebug = true; // TODO
//     // l._setMemory();
//     // l.printMemory();
//     // l.save();
//     l.load();
//     l.printStatus();
//     l.main();
//     // cout << zfill(21) << endl;
//     // cout << "END" << endl;
//     return 0;
// };