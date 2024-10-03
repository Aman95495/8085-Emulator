
#include "../header/processor.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>
#include <sstream>
using namespace std;

// Constructor
Processor:: Processor() {
    // Initialize registers
    registers["A"] = 0;
    registers["B"] = 0;
    registers["C"] = 0;
    registers["D"] = 0;
    registers["E"] = 0;
    registers["H"] = 0;
    registers["L"] = 0;
    registers["SP"] = 0;
    registers["PC"] = 0;

    // Initialize flags
    flag["Z"] = false;  // Zero flag
    flag["S"] = false;  // Sign flag
    flag["P"] = false;  // Parity flag
    flag["CY"] = false; // Carry flag
    flag["AC"] = false; // Auxiliary carry flag

    // Register Pairs
    registerPair["B"] = "C";
    registerPair["D"] = "E";
    registerPair["H"] = "L";

    // Clear memory map
    memory.clear();

    // Memory size - 64KB i.e 65536;
    memSize = hexToDec("FFFF");
}


// Method to set the value of a register
void Processor::setRegister(const string& regName, int value) {
    if(registers.find(regName) != registers.end()){
        registers[regName] = value;
    }
    else{
        cerr<<"Invalid Register Mentioned :: "<< regName <<endl;
    }
}

// Method to get the value of a register
int Processor::getRegister(const string& regName){
    if(registers.find(regName) != registers.end()){
        return registers[regName];
    }
    else{
        cerr<<"Invalid Register Mentioned :: "<< regName <<endl;
        return  -1;
    }
}


// Method to set the value of a flag register
void Processor::setFlag(const string& regName, int value) {
    if(flag.find(regName) != flag.end()){
        flag[regName] = value;
    }
    else{
        cerr<<"Invalid Register Mentioned :: "<< regName <<endl;
    }
}

// Method to get the value of a flag register
int Processor::getFlag(const string& regName){
    if(flag.find(regName) != flag.end()){
        return flag[regName];
    }
    else{
        cerr<<"Invalid Register Mentioned"<< regName <<endl;
        return  -1;
    }
}


// Method to set value at memory address
void Processor::setMemory(int addr, int data){
    // Checking for valid address
    if (addr < 0 || addr >= memSize) {
        cout << "Address out of range :: " << addr <<endl;
        return;
    }
    
    memory[addr] = data;
}

// Method to retrieve value from memory address
int Processor::getMemory(int addr){
    // Checking for valid address
    if (addr < 0 || addr >= memSize) {
        cout << "Address out of range :: " << addr <<endl;
        return -1;
    }
  
    return memory[addr];
}

// get lower order register
string Processor::getPair(string regName){
    if(registers.find(regName) != registers.end()){
        return registerPair[regName];
    }
    else{
        cerr<<"Invalid Register Mentioned :: "<< regName <<endl;
        return  "-1";
    }
}

// display status of all registers
void  Processor::displayRegister(){
    cout << "+--------------------------------------------+" << endl;
    cout << "| A  | B  | C  | D  | E  | H  | L  | PC | SP |" << endl;
    cout << "+--------------------------------------------+" << endl;
    
    cout << "| ";
    for (const auto& pair : registers) {
        cout << setw(2) << setfill('0') << decToHex(pair.second) << " | ";
    }
    cout << endl;

    cout << "+--------------------------------------------+" << endl;
}

// display status of all flag registers
void Processor::displayFlag() {
    cout << "+------------------------+" << endl;
    cout << "| Z  | S  | P  | CY | AC |" << endl;
    cout << "+------------------------+" << endl;  

    cout << "| ";
    cout << setw(2) << setfill('0') << flag["Z"] << " | ";
    cout << setw(2) << setfill('0') << flag["S"] << " | ";
    cout << setw(2) << setfill('0') << flag["P"] << " | ";
    cout << setw(2) << setfill('0') << flag["CY"] << " | ";
    cout << setw(2) << setfill('0') << flag["AC"] << " | ";
    cout << endl;
    
    cout << "+------------------------+" << endl;  
}



// Function to convert decimal number to hexadecimal
string Processor::decToHex(int decValue) {
    stringstream ss;
    ss << uppercase << hex << decValue;
    return ss.str();
}

// Function to convert hexadecimal number to decimal
int Processor::hexToDec(string hexValue) {
    int decValue;
    stringstream ss;
    ss << hex << hexValue;
    ss >> decValue;

    if (ss.fail() || !ss.eof()) {
        cout<<"Invalid Hexadecimal Value :: "<<hexValue<<endl;
    }

    return decValue;
}