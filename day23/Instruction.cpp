#include "Instruction.h"
#include <iostream>
#include <regex>

Instruction::Instruction(std::string i, std::string a1, std::string a2) :  ins(i), arg1(a1), arg2(a2) {}

Instruction::Instruction(std::string instructionText){
  std::regex instruction_regex("([a-z]+) ([a-z0-9-]+)[ ]*([a-z0-9-]*)");

  std::smatch ins_match;

  if(std::regex_search(instructionText,ins_match,instruction_regex)){
      std::cout << "Matched (" << ins_match[1]  << ") (" << ins_match[2] << ")";
      if (ins_match.size()>3){
          std::cout << " (" << ins_match[3] << ")";
      }
      std::cout << "\n";
      ins=ins_match[1];
      arg1=ins_match[2];
      arg2=ins_match[3];
  }
}

void Instruction::execute(std::map<std::string,long long int> &memory, int &pc, std::vector<long int> &rcv, std::vector<long int> &snd){
  std::cout << ins << " " << arg1 << " " << arg2 << "\n";
  if(ins== "snd"){
    snd.push_back(resolve(arg1,memory));
    pc++;
  }
  else if(ins==  "set"){
    memory[arg1]=resolve(arg2,memory);
    pc++;
  }
  else if(ins==  "add"){
    memory[arg1]=memory[arg1]+resolve(arg2,memory);
    pc++;
  }
  else if(ins==  "sub"){
    memory[arg1]=memory[arg1]-resolve(arg2,memory);
    pc++;
  }
  else if(ins== "mul"){
    memory[arg1]=memory[arg1]*resolve(arg2,memory);
    pc++;
  }
  else if(ins=="mod"){
    memory[arg1]=memory[arg1] % resolve(arg2,memory);
    pc++;
  }
  else if(ins== "rcv"){
    if(rcv.size()>0){
      memory[arg1]=*rcv.begin();
      rcv.erase(rcv.begin());
      pc++;
    }
  }
  else if(ins=="jgz"){
    if(resolve(arg1,memory)>0){
      pc+=resolve(arg2,memory);
    }
    else{
      pc++;
    }
  }
  else if(ins=="jnz"){
    if(resolve(arg1,memory)!=0){
      pc+=resolve(arg2,memory);
    }
    else{
      pc++;
    }
  }
  else{
    std::cout << "oops\n";
    pc++;
  }
}

long long int Instruction::resolve(std::string s,std::map<std::string,long long int> memory){
  if((s[0]>='0' && s[0]<='9' ) || s[0]=='-' ){
    long long int resolved=stoi(s);
    return resolved;
  }else{
    long long int resolved=memory[s];
    return resolved;
  }
}
