#ifndef EXECUTE_H
#define EXECUTE_H
#include <string>
#include "../header/processor.h"
using namespace std;


class Execute{
    public:
        void SET(Processor &cpu, int addr, int value);
        void MVI(Processor &cpu ,string regName, int value);
        void MOV(Processor &cpu ,string regName1, string regName2);
        void ADD(Processor &cpu, string regName);
        void ADC(Processor &cpu, string regName);
        void ADI(Processor &cpu, int Value);
        void ACI(Processor &cpu, int Value);
        void SUB(Processor &cpu, string regName);
        void SBB(Processor &cpu, string regName);
        void SUI(Processor &cpu, int Value);
        void SBI(Processor &cpu, int Value);
        void INR(Processor &cpu, string regName);
        void INX(Processor &cpu, string regName);
        void DCR(Processor &cpu, string regName);
        void DCX(Processor &cpu, string regName);
        void LXI(Processor &cpu, string regName, string value);
        
        
        void JMP(Processor &cpu, int address);
};


#endif