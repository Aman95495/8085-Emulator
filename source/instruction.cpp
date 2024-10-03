#include "../header/instruction.h"
#include "../header/processor.h"
#include "../header/execute.h"
#include <iostream>
#include <map>
#include  <string>
#include <algorithm>
using namespace std;


// Constructor definition
Instruction::Instruction() {
        Valid_Instructions["SET"] = 0;

        // Control Instructions
        Valid_Instructions["NOP"] = 0;
        Valid_Instructions["HLT"] = 0;
        Valid_Instructions["DI"] = 0;
        Valid_Instructions["EI"] = 0;
        Valid_Instructions["RIM"] = 0;
        Valid_Instructions["SIM"] = 0;

        // Logical Instructions
        Valid_Instructions["CMP"] = 1;
        Valid_Instructions["CPI"] = 2;
        Valid_Instructions["ANA"] = 1;
        Valid_Instructions["ANI"] = 2;
        Valid_Instructions["XRA"] = 1;
        Valid_Instructions["XRI"] = 2;
        Valid_Instructions["ORA"] = 1;
        Valid_Instructions["ORI"] = 2;
        Valid_Instructions["RLC"] = 1;
        Valid_Instructions["RRC"] = 1;
        Valid_Instructions["RAL"] = 1;
        Valid_Instructions["RAR"] = 1;
        Valid_Instructions["CMA"] = 1;
        Valid_Instructions["CMC"] = 1;
        Valid_Instructions["STC"] = 1;

        // Branching Instructions
        Valid_Instructions["JMP"] = 3;
        Valid_Instructions["JC"] = 3;
        Valid_Instructions["JNC"] = 3;
        Valid_Instructions["JP"] = 3;
        Valid_Instructions["JM"] = 3;
        Valid_Instructions["JZ"] = 3;
        Valid_Instructions["JNZ"] = 3;
        Valid_Instructions["JPE"] = 3;
        Valid_Instructions["JPO"] = 3;
        Valid_Instructions["CALL"] = 3;
        Valid_Instructions["CC"] = 3;
        Valid_Instructions["CNC"] = 3;
        Valid_Instructions["CP"] = 3;
        Valid_Instructions["CM"] = 3;
        Valid_Instructions["CZ"] = 3;
        Valid_Instructions["CNZ"] = 3;
        Valid_Instructions["CPE"] = 3;
        Valid_Instructions["CPO"] = 3;
        Valid_Instructions["RET"] = 1;
        Valid_Instructions["RC"] = 1;
        Valid_Instructions["RNC"] = 1;
        Valid_Instructions["RP"] = 1;
        Valid_Instructions["RM"] = 1;
        Valid_Instructions["RZ"] = 1;
        Valid_Instructions["RNZ"] = 1;
        Valid_Instructions["RPE"] = 1;
        Valid_Instructions["RPO"] = 1;
        Valid_Instructions["PCHL"] = 1;

        // Arithmetic Instructions
        Valid_Instructions["ADD"] = 1;
        Valid_Instructions["ADC"] = 1;
        Valid_Instructions["ADI"] = 2;
        Valid_Instructions["ACI"] = 2;
        Valid_Instructions["LXI"] = 3;
        Valid_Instructions["DAD"] = 1;
        Valid_Instructions["SUB"] = 1;
        Valid_Instructions["SBB"] = 1;
        Valid_Instructions["SUI"] = 2;
        Valid_Instructions["SBI"] = 2;
        Valid_Instructions["INR"] = 1;
        Valid_Instructions["INX"] = 1;
        Valid_Instructions["DCR"] = 1;
        Valid_Instructions["DCX"] = 1;
        Valid_Instructions["DAA"] = 1;

        // Data Transfer Instructions
        Valid_Instructions["MOV"] = 1;
        Valid_Instructions["MVI"] = 2;
        Valid_Instructions["LDA"] = 3;
        Valid_Instructions["LDAX"] = 1;
        Valid_Instructions["LXI"] = 3;
        Valid_Instructions["LHLD"] = 3;
        Valid_Instructions["STA"] = 3;
        Valid_Instructions["STAX"] = 1;
        Valid_Instructions["SHLD"] = 3;
        Valid_Instructions["XCHG"] = 1;
        Valid_Instructions["SPHL"] = 1;
        Valid_Instructions["XTHL"] = 1;
        Valid_Instructions["PUSH"] = 1;
        Valid_Instructions["POP"] = 1;
        Valid_Instructions["OUT"] = 2;
        Valid_Instructions["IN"] = 2;

        // Custom Instructions
        Valid_Instructions["RST"] = 1;

}

void Instruction::processInstructions(Processor &cpu, vector<string> Instruction_Set){
        for(string  instruction : Instruction_Set) {
                int pos = instruction.find(' ');
                string inst = instruction.substr(0, pos);
                string operand = instruction.substr(pos+1, instruction.length()-pos+1);

                if(Valid_Instructions.find(inst)  == Valid_Instructions.end()) {
                        cout << "Invalid Instruction: " << instruction << endl;
                }
                else{
                        Execute exec;
                        if(inst == "SET"){
                                string addr = "";
                                int loc = 0;
                                for(char ch: operand){
                                        if(ch == 32){
                                                break;
                                        }
                                        addr+=ch;
                                        loc++;
                                }
                                string value = operand.substr(loc+1, operand.length()-(loc+1));
                                exec.SET(cpu, cpu.hexToDec(addr), cpu.hexToDec(value));
                        }
                        else if(inst == "MVI"){
                                string regName(1, operand[0]);
                                string value = operand.substr(2, operand.length()-2);
                                exec.MVI(cpu, regName, cpu.hexToDec(value));
                        }
                        else if(inst == "MOV"){
                                string regName1(1, operand[0]);
                                string regName2 = "";
                                for(int i=1; i<operand.size(); i++){
                                        if(operand[i]>='A' && operand[i]<='Z'){
                                                regName2 += operand[i];
                                        }
                                }
                                exec.MOV(cpu, regName1, regName2);
                        }
                        else if (inst == "ADD") {
                                exec.ADD(cpu, operand);
                        }
                        else if (inst == "ADC") {
                                exec.ADC(cpu, operand);
                        }
                        else if (inst == "ADI") {
                                exec.ADI(cpu, cpu.hexToDec(operand));
                        }
                        else if (inst == "ACI") {
                                exec.ACI(cpu, cpu.hexToDec(operand));
                        }
                        else if (inst == "SUB") {
                                exec.SUB(cpu, operand);
                        }
                        else if (inst == "SBB") {
                                exec.SBB(cpu, operand);
                        }
                        else if (inst == "SUI") {
                                exec.SUI(cpu, cpu.hexToDec(operand));
                        }
                        else if (inst == "SBI") {
                                exec.SBI(cpu, cpu.hexToDec(operand));
                        }
                        else if (inst == "INR") {
                                exec.INR(cpu, operand);
                        }
                        else if (inst == "DCR") {
                                exec.DCR(cpu, operand);
                        }
                        else if (inst == "LXI") {
                                string regName(1, operand[0]);
                                string value = "";
                                for(char ch: operand.substr(1, operand.length()-1)){
                                        if(ch != 32 && ch != ','){
                                                value += ch;
                                        }
                                }
                                exec.LXI(cpu, regName, value);
                        }

                        else if (inst == "JMP") {
                                exec.JMP(cpu, stoi(operand));
                        }
                }

        }
}