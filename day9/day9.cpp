#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class GarbageParser
{
private:
  int score{0};
  int currentGroupLevel{0};
  bool inGarbage{false};
  bool ignoreNext{false};
  int groupOpenCount{0};
  int groupCloseCount{0};
  int garbageCount{0};
public:
  void parseString(const string &);
  int getScore();
  int getGarbageCount();
};


void GarbageParser::parseString(const string &inputString){
  for(char c:inputString){
    if(!ignoreNext){
      switch(c){
        case '{':
          if(!inGarbage){
            groupOpenCount++;
            currentGroupLevel++;
          }
          else{
            garbageCount++;
          }
          break;
        case '}':
          if(!inGarbage){
            groupCloseCount++;
            score+=currentGroupLevel;
            currentGroupLevel--;
          }
          else{
            garbageCount++;
          }
          break;
        case '<':
          if(!inGarbage){
            inGarbage=true;
          }else{
            garbageCount++;
          }
          break;
        case '>':
          inGarbage=false;
          break;
        case '!':
          ignoreNext=true;
          break;
        default:
          if(inGarbage){
            garbageCount++;
          }
          break;
      }
    }
    else{
      cout << c << " ignored.\n";
      ignoreNext=false;
    }
  }
}

int GarbageParser::getScore(){
  return score;
}

int GarbageParser::getGarbageCount(){
  return garbageCount;
}

int main(int argc,char* argv[]){
  if(argc < 1){
    cout << "Usage: " << argv[0] << " inputFile\n";
  }else{
    ifstream inputFile(argv[1]);
    string inputString;
    getline(inputFile,inputString);
    cout << "Input:\n";
    cout << inputString;

    GarbageParser parser;
    parser.parseString(inputString);

    cout << "Score: " << parser.getScore() << "\n";
    cout << "Garbage: " << parser.getGarbageCount() << "\n";

  }
}
