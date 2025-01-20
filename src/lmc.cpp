#include <fstream>
#include <iostream>
#include <vector>
#include "lmc.h"
#include "utils.h"

using namespace std;

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
    cin >> acc;
}
void Lmc::out()
{
    // print acc
    cout << acc << endl;
}
void Lmc::otc()
{
    // print acc as ascii
    cout << (char)acc << endl;
}
void Lmc::hlt()
{
    isRunning = false;
}
void Lmc::hlt(string errorMsg)
{
    cout << errorMsg << endl; // TODO: int codes?
    hlt();
}

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
            cout << "Unknown instruction: " << ir << ". With address: " << ar << endl;
            break;
        }
        break;
    case HLT:
        hlt();
        break;
    default:
        cout << "unknown instruction: " << ir << endl;
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
    while (isRunning)
    {
        if (isDebug)
        {
            cout << endl;
            printStatus();
        }
        step();
    }
}

void Lmc::reset()
{
    fill(begin(memory), end(memory), 0);
    acc = 0;
    pc = 0;
    ir = 0;
    ar = 0;
}

array<int, 100> Lmc::getMemory()
{
    return memory;
}

void Lmc::setMemory(vector<int> m)
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
            cout << endl;
        }
        cout << zfill(memory[i]) << ", ";
    }
    cout << endl;
}

void Lmc::save()
{
    ofstream file(FILEPATH);
    file.close();
}

void Lmc::load()
{
    ifstream file(FILEPATH);
    if (isDebug)
    {
        cout << "Loading from " << FILEPATH << endl;
    }
    string fileBuffer;
    vector<int> m;
    int i = 0;
    while (getline(file, fileBuffer))
    {
        try
        {
            int buffer = stoi(fileBuffer);
            m.push_back(buffer);
            i++;
        }
        catch (const invalid_argument &ia)
        {
            if (isDebug)
            {
                cout << "Skipping line: " << fileBuffer << endl;
            }
        }
    }
    file.close();
    setMemory(m);
}

void Lmc::printRegistries()
{
    cout << "PC: " << pc << ". IR: " << ir << ". AR: " << ar << ". ACC: " << acc << "." << endl;
}

void Lmc::printStatus()
{
    printRegistries();
    printMemory();
}

// TODO
// - Compile from Assembly to dec.2
// - Add saving to file
// - Create TUI using ncurses.
// - Refactor (h file)
// - Comment
// - readme.md
// - publish

int main()
{
    cout << "START" << endl;
    Lmc l;
    l.isDebug = false; // TODO
    // l._setMemory();
    // l.printMemory();
    // l.save();
    l.load();
    l.printStatus();
    l.main();
    // cout << zfill(21) << endl;
    cout << "END" << endl;
    return 0;
};