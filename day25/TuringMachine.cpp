#include <map>
#include <iostream>
#include "TuringMachine.h"


TuringMachine::TuringMachine(char initState): currentPos(0),currentState(initState) {}

std::map<int,bool> TuringMachine::getTape(){
  return tape;
}

void TuringMachine::executeStep(){
  //std::cout << currentPos << "\n";
  bool value=tape[currentPos];
  switch(currentState){
    case 'A':
      if(value){
        doStep(false,-1,'E');
      }else{
        doStep(true,1,'B');
      }
      break;
    case 'B':
      if(value){
        doStep(false,1,'A');
      }else{
        doStep(true,-1,'C');
      }
      break;
    case 'C':
      if(value){
        doStep(false,1,'C');
      }else{
        doStep(true,-1,'D');
      }
      break;
    case 'D':
      if(value){
        doStep(false,-1,'F');
      }else{
        doStep(true,-1,'E');
      }
      break;
    case 'E':
      if(value){
        doStep(true,-1,'C');
      }else{
        doStep(true,-1,'A');
      }
      break;
    case 'F':
      if(value){
        doStep(true,1,'A');
      }else{
        doStep(true,-1,'E');
      }
      break;
  }
}

inline void TuringMachine::doStep(bool write,int move, char nextState){
  tape[currentPos]=write;
  currentPos+=move;
  currentState=nextState;
}
