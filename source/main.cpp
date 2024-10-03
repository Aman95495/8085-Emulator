#include "../header/processor.h"
#include "../header/instruction.h"
#include "../header/execute.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

void use_prewritten_instructions(Processor &cpu,const string& filename) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Error opening the file" << endl;
        return;
    }

    vector<string> instructions; 

    string line;
    while (getline(inputFile, line)) {
        if (!line.empty()) { // Check if the line is not empty
            instructions.push_back(line);
        }
    }

    Instruction run;
    run.processInstructions(cpu, instructions);

    inputFile.close();
}



void write_instructions(Processor &cpu){
    ofstream outputFile("../test/userInput.txt"); 

    if (!outputFile.is_open()) {
        cout << "Error opening the file." << endl;
        return;
    }

    string  instruction;
    
    do{
        getline(cin, instruction);
        outputFile << instruction <<endl;
    }while(instruction != "HLT");

    outputFile.close();

    use_prewritten_instructions(cpu,"../test/userInput.txt");
}





int main(){
    int choice;
    Processor  cpu = Processor();
    do{
        cout<<"\n\n\n*****************************************************************\n";
        cout<<"1. Write Instructions"<<endl;
        cout<<"2. Use Pre-Written Instructions"<<endl;
        cout<<"3. Display Status of 8085"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter Your Choice :: ";
        cin>>choice;

        switch(choice){
            case 1: write_instructions(cpu);
                    break;
            case 2: use_prewritten_instructions(cpu,"../test/input1.txt");
                    break;
            case 3: cpu.displayRegister();
                    cpu.displayFlag();
                    break;
            case 4: cout<<"Thank you for using 8085 Emulator"<<endl;
                    break;
            default: cout<<"Invalid Choice"<<endl;
                    break;
        }    
    }while(choice!=4);


    return 0;
}