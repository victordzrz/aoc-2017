#include <iostream>
#include <fstream>
#include <map>
#include <tuple>

using namespace std;

enum class State{
  Cleaned=0,Weakened,Infected,Flagged
};

tuple<int,int> turn_left(tuple<int,int> direction){
  //cout << "left ";
  int x,y;
  tie(x,y)=direction;
  return make_tuple(y,-x);
}

tuple<int,int> reverse(tuple<int,int> direction){
  //cout << "reverse ";
  int x,y;
  tie(x,y)=direction;
  return make_tuple(-x,-y);
}

tuple<int,int> turn_right(tuple<int,int> direction){
  //cout << "right ";
  int x,y;
  tie(x,y)=direction;
  return make_tuple(-y,x);
}

tuple<int,int> move(tuple<int,int> position, tuple<int,int> direction){
  int x,y,dir_x,dir_y;
  tie(x,y)=position;
  tie(dir_x,dir_y)=direction;
  return make_tuple(x+dir_x,y+dir_y);
}

void print_position(tuple<int,int> pos){
  int x,y;
  tie(x,y)=pos;
  cout << "(" << x << "," << y << ")";
}

int main(int argc, char * argv[]){
  if(argc < 1){
    cout << "Usage: " << argv[0] << " inputFile\n";
  }else{
    ifstream inputFile(argv[1]);
    std::string inputString;
    std::map<std::tuple<int,int>,State> infected_map;

    getline(inputFile,inputString);
    int y=0;
    int x=0;
    while(inputString.size()>0){
      x=0;
      for(char c:inputString){
        if(c=='.'){
          infected_map[make_tuple(x,y)]=State::Cleaned;
        }
        else if(c=='#'){
          infected_map[make_tuple(x,y)]=State::Infected;
        }
        x++;
      }
      y++;
      getline(inputFile,inputString);
    }
    cout << "max x " << x << "\n";
    cout << "max y " << y << "\n";
    auto position=make_tuple(((x)/2),((y)/2));
    print_position(position);
    cout << "\n";
    auto direction=make_tuple(0,-1);
    int infected_turn_count=0;

    int burst_limit=10000000;
    for(int i=0;i<burst_limit;i++){
      //print_position(position);
      //cout << (int)infected_map[position] << " " ;

      switch(infected_map[position]){
        case State::Infected:
          direction=turn_right(direction);
          infected_map[position]=State::Flagged;
          break;
        case State::Weakened:
          infected_map[position]=State::Infected;
          infected_turn_count++;
          break;
        case State::Flagged:
          direction=reverse(direction);
          infected_map[position]=State::Cleaned;
          break;
        case State::Cleaned:
          direction=turn_left(direction);
          infected_map[position]=State::Weakened;
          break;
        default:
          cout << "Ooops\n";
      }

      position=move(position,direction);
      //print_position(position);

      //cout << "\n";
      if(i%100000==0){
        cout << i << "\n";
      }
    }
    cout << "Turned to infected: " << infected_turn_count << "\n";
  }
  return 0;
}
