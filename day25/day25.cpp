#include <iostream>
#include <numeric>

#include "TuringMachine.h"

using namespace std;

int main(int argc, char * argv[]){
  TuringMachine tm('A');

  int steps=12386363;
  for(int i=0;i<steps;i++){
    tm.executeStep();
  }

  auto tape=tm.getTape();
  int result=accumulate(tape.cbegin(),tape.cend(),0,[]
  (const int &sum,const pair<int,bool> &p2){
    if(p2.second){
      return sum+1;
    }
    return sum;
  });

  cout<< "Checksum :" << result << "\n";

}
