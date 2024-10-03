#include "../header/execute.h"
#include "../header/processor.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

bool isEvenOnes(int n)
{
    int count = 0;

    while (n > 0)
    {
        count += n & 1;
        n >>= 1;
    }

    return count % 2 == 0;
}

void Execute::SET(Processor &cpu, int addr, int Value)
{
    cpu.setMemory(addr, Value);
}

void Execute::MVI(Processor &cpu, string regName, int Value)
{
    if (regName == "M")
    {
        int h = cpu.getRegister("H");
        int l = cpu.getRegister("L");
        int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
        cpu.setMemory(addr, Value);
    }
    else if (cpu.getRegister(regName) != -1)
    {
        cpu.setRegister(regName, Value);
    }
}

void Execute::MOV(Processor &cpu, string regName1, string regName2)
{
    if ((cpu.getRegister(regName1) != -1) && (regName2 == "M"))
    {
        int h = cpu.getRegister("H");
        int l = cpu.getRegister("L");
        int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
        int regValue = cpu.getMemory(addr);
        cpu.setRegister(regName1, regValue);
    }
    else if ((cpu.getRegister(regName1) != -1) && (cpu.getRegister(regName2) != -1))
    {
        cpu.setRegister(regName1, cpu.getRegister(regName2));
    }
}

void Execute::ADD(Processor &cpu, string regName)
{
    if ((regName == "M") || (cpu.getRegister(regName) != -1))
    {
        int acc = cpu.getRegister("A");
        int regValue;
        if (regName == "M")
        {
            int h = cpu.getRegister("H");
            int l = cpu.getRegister("L");
            int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
            regValue = cpu.getMemory(addr);
        }
        else
        {
            regValue = cpu.getRegister(regName);
        }
        acc += regValue;
        int new_value = acc < 256 ? acc : (acc - 256);
        cpu.setRegister("A", new_value);

        // Adjust flags
        cpu.setFlag("Z", (new_value == 0));
        cpu.setFlag("S", (acc < 0));
        cpu.setFlag("P", isEvenOnes(new_value));
        cpu.setFlag("CY", (acc > 255));
    }
}

void Execute::ADC(Processor &cpu, string regName)
{
    if ((regName == "M") || (cpu.getRegister(regName) != -1))
    {
        int acc = cpu.getRegister("A");
        int regValue;
        if (regName == "M")
        {
            int h = cpu.getRegister("H");
            int l = cpu.getRegister("L");
            int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
            regValue = cpu.getMemory(addr);
        }
        else
        {
            regValue = cpu.getRegister(regName);
        }
        acc += regValue + (cpu.getFlag("CY") ? 1 : 0);
        int new_value = acc < 256 ? acc : (acc - 256);
        cpu.setRegister("A", new_value);

        // Adjust flags
        cpu.setFlag("Z", (new_value == 0));
        cpu.setFlag("S", (acc < 0));
        cpu.setFlag("P", isEvenOnes(new_value));
        cpu.setFlag("CY", (acc > 255));
    }
}

void Execute::ADI(Processor &cpu, int Value)
{
    int acc = cpu.getRegister("A");
    acc += Value;
    int new_value = acc < 256 ? acc : (acc - 256);
    cpu.setRegister("A", new_value);

    // Adjust flags
    cpu.setFlag("Z", (new_value == 0));
    cpu.setFlag("S", (acc < 0));
    cpu.setFlag("P", isEvenOnes(new_value));
    cpu.setFlag("CY", (acc > 255));
}

void Execute::ACI(Processor &cpu, int Value)
{
    int acc = cpu.getRegister("A");
    acc += Value + (cpu.getFlag("CY") ? 1 : 0);
    int new_value = acc < 256 ? acc : (acc - 256);
    cpu.setRegister("A", new_value);

    // Adjust flags
    cpu.setFlag("Z", (new_value == 0));
    cpu.setFlag("S", (acc < 0));
    cpu.setFlag("P", isEvenOnes(new_value));
    cpu.setFlag("CY", (acc > 255));
}

void Execute::SUB(Processor &cpu, string regName)
{
    if ((regName == "M") || (cpu.getRegister(regName) != -1))
    {
        int acc = cpu.getRegister("A");
        int regValue;
        if (regName == "M")
        {
            int h = cpu.getRegister("H");
            int l = cpu.getRegister("L");
            int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
            ;
            regValue = cpu.getMemory(addr);
        }
        else
        {
            regValue = cpu.getRegister(regName);
        }
        acc -= regValue;
        int new_value = (acc >= 0) ? acc : (acc + 256);
        cpu.setRegister("A", new_value);

        // Adjust flags
        cpu.setFlag("Z", (new_value == 0));
        cpu.setFlag("S", (acc < 0));
        cpu.setFlag("P", isEvenOnes(new_value));
        cpu.setFlag("CY", (acc < 0));
    }
}

void Execute::SBB(Processor &cpu, string regName)
{
    if ((regName == "M") || (cpu.getRegister(regName) != -1))
    {
        int acc = cpu.getRegister("A");
        int regValue;
        if (regName == "M")
        {
            int h = cpu.getRegister("H");
            int l = cpu.getRegister("L");
            int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
            ;
            regValue = cpu.getMemory(addr);
        }
        else
        {
            regValue = cpu.getRegister(regName);
        }
        acc -= regValue + (cpu.getFlag("CY") ? 1 : 0);
        int new_value = (acc >= 0) ? acc : (acc + 256);
        cpu.setRegister("A", new_value);

        // Adjust flags
        cpu.setFlag("Z", (new_value == 0));
        cpu.setFlag("S", (acc < 0));
        cpu.setFlag("P", isEvenOnes(new_value));
        cpu.setFlag("CY", (acc < 0));
    }
}

void Execute::SUI(Processor &cpu, int Value)
{
    int acc = cpu.getRegister("A");
    acc -= Value;
    int new_value = (acc >= 0) ? acc : (acc + 256);
    cpu.setRegister("A", new_value);

    // Adjust flags
    cpu.setFlag("Z", (new_value == 0));
    cpu.setFlag("S", (acc < 0));
    cpu.setFlag("P", isEvenOnes(new_value));
    cpu.setFlag("CY", (acc < 0));
}

void Execute::SBI(Processor &cpu, int Value)
{
    int acc = cpu.getRegister("A");
    acc -= Value + (cpu.getFlag("CY") ? 1 : 0);
    int new_value = (acc >= 0) ? acc : (acc + 256);
    cpu.setRegister("A", new_value);

    // Adjust flags
    cpu.setFlag("Z", (new_value == 0));
    cpu.setFlag("S", (acc < 0));
    cpu.setFlag("P", isEvenOnes(new_value));
    cpu.setFlag("CY", (acc < 0));
}

void Execute::INR(Processor &cpu, string regName)
{
    int new_value;
    int final_value;
    if ((regName == "M"))
    {
        int h = cpu.getRegister("H");
        int l = cpu.getRegister("L");
        int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
        new_value = cpu.getMemory(addr) + 1;
        final_value = new_value < 256 ? new_value : (new_value - 256);
        cpu.setMemory(addr, final_value);
    }
    else if (cpu.getRegister(regName) != -1)
    {
        new_value = cpu.getRegister(regName) + 1;
        final_value = new_value < 256 ? new_value : (new_value - 256);
        cpu.setRegister(regName, final_value);
    }
    // Adjust flags
    cpu.setFlag("Z", (final_value == 0));
    cpu.setFlag("S", (new_value < 0));
    cpu.setFlag("P", isEvenOnes(final_value));
    cpu.setFlag("CY", (new_value > 255));
}

void Execute::DCR(Processor &cpu, string regName)
{
    int new_value;
    int final_value;
    if ((regName == "M"))
    {
        int h = cpu.getRegister("H");
        int l = cpu.getRegister("L");
        int addr = cpu.hexToDec(cpu.decToHex(h) + cpu.decToHex(l));
        new_value = cpu.getMemory(addr) - 1;
        final_value = (new_value >= 0) ? new_value : (new_value + 256);
        cpu.setMemory(addr, final_value);
    }
    else if (cpu.getRegister(regName) != -1)
    {
        new_value = cpu.getRegister(regName) - 1;
        final_value = (new_value >= 0) ? new_value : (new_value + 256);
        cpu.setRegister(regName, final_value);
    }
    // Adjust flags
    cpu.setFlag("Z", (final_value == 0));
    cpu.setFlag("S", (new_value < 0));
    cpu.setFlag("P", isEvenOnes(final_value));
    cpu.setFlag("CY", (new_value < 0));
}

void Execute::LXI(Processor &cpu, string regName, string Value){
    if(cpu.getPair(regName).compare("-1") != 0){
        int value1 = cpu.hexToDec(Value.substr(0, 2));
        int value2 = cpu.hexToDec(Value.substr(2, 2));
        string regName2 = cpu.getPair(regName);

        cpu.setRegister(regName, value1);
        cpu.setRegister(regName2, value2);
    }
}

// void Execute::INX(Processor &cpu, string regName){
//     if(cpu.getPair(regName).compare("-1") != 0){
//         string regName2
//     }
// }






void Execute::JMP(Processor &cpu, int address)
{
    cpu.setRegister("PC", address);
}
