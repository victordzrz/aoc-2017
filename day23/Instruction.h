#include <map>
#include <string>
#include <vector>

#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#endif

class Instruction{
public:
  std::string ins;
  std::string arg1;
  std::string arg2;
  Instruction(std::string i, std::string a1, std::string a2);
  Instruction(std::string instructionText);
  void execute(std::map<std::string,long long int> &memory, int &pc, std::vector<long int> &rcv, std::vector<long int> &snd);
private:
  long long int resolve(std::string s,std::map<std::string,long long int> memory);
};
