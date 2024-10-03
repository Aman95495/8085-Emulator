#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <string>
#include <map>
#include <sstream>
using namespace std;

class Processor{
    private:
        map<string, int> registers;
        map<string, int> flag;
        map<int, int> memory;
        map<string, string> registerPair;
        int memSize;

    public:

        Processor();

        // set and get register value
        void setRegister(const string &regName, const int regValue);
        int getRegister(const string &regName);

        // set and get flag registers value
        void setFlag(const string &regName, const int regValue);
        int getFlag(const string &regName);

        // set and get value from memory address
        void setMemory(const  int memAddr, const int memValue);
        int getMemory(const int memAddr);

        // get lower order register from higher order
        string getPair(string regName);

        // display Current status of all registers, flag registers & memory
        void displayRegister();
        void displayFlag();

        // for conversion
        string decToHex(int decValue);
        int hexToDec(string hexValue);

};

#endif
