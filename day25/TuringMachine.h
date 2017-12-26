#include<map>

class TuringMachine {
public:
  std::map<int,bool> getTape();
  void executeStep();
  TuringMachine(char initState);
private:
  std::map<int,bool> tape;
  int currentPos;
  char currentState;
  void doStep(bool write,int move, char nextState);
};
