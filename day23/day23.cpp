#include <iostream>
#include <fstream>
#include <string>
#include "Instruction.h"
#include <cmath>

using namespace std;

bool is_prime(int number){
  for(int i=2;i<=sqrt(number);i++){
    if(number % i ==0){
      return false;
    }
  }
  return true;
}

int equivalent(){
  int b=106500;
  int c=123500;
  int h=0;
  do{
    if(!is_prime(b)){
      h++;
    }
    b+=17;
  }while((b-17)!=c); // A bit weird, but the condition is checked before the increment
  return h;
}

int main(int argc, char * argv[]){
  if(argc < 1){
    cout << "Usage: " << argv[0] << " inputFile\n";
  }else{
    ifstream inputFile(argv[1]);
    std::string inputString;
    vector<Instruction> program;

    getline(inputFile,inputString);
    cout << "Input:\n";
    cout << inputString << "\n";
    while(inputString.size()>0){
      program.push_back(Instruction(inputString));
      getline(inputFile,inputString);
    }
    map<string,long long int> memory0;
    int pc0=0;
    vector<long int> msg0;
    int mul_count=0;

    while(pc0<program.size()){
      auto instruction=program[pc0];
      if(instruction.ins=="mul"){
        mul_count++;
      }
      cout << pc0 << ": ";
      instruction.execute(memory0,pc0, msg0,msg0);
    }

    cout << "Multiplications: "  << mul_count << "\n";

    cout << "Equivalent h: " << equivalent() << "\n";
  }
  return 0;
}
