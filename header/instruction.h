#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "../header/processor.h"
using namespace std;

class Instruction{
    private:
        map<string, int> Valid_Instructions;

    public:
        Instruction();

        void processInstructions(Processor &cpu, vector<string> Instruction_Set);
};

#endif