#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <tuple>
#include <vector>

using namespace std;

tuple<int,int> get_next_position(tuple<int,int> &pos){
  int x,y;
  tie(x,y)=pos;
  int dir_x,dir_y;
  if (abs(x) == abs(y)){
    if(x>=0){
      if(y<=0){
        dir_x=1;
        dir_y=0;
      }
      else{
        dir_x=-1;
        dir_y=0;
      }
    }
    else{
      if(y>0){
        dir_x=0;
        dir_y=-1;
      }
      if(y<0){
        dir_x=1;
        dir_y=0;
      }
    }
  }
  if (x>0 && abs(y)<abs(x)){
    dir_x=0;
    dir_y=1;
  }
  if(x<0 && abs(y)<abs(x)){
    dir_x=0;
    dir_y=-1;
  }
  if(y>0 && abs(x)<abs(y)){
    dir_x=-1;
    dir_y=0;
  }
  if(y<0 && abs(x)<abs(y)){
    dir_x=1;
    dir_y=0;
  }

  return make_tuple(x+dir_x,y+dir_y);
}

int part1(int input){
  tuple<int,int> position=make_tuple(0,0);
  int value=1;
  int x,y;
  while(value<input){
    position=get_next_position(position);
    tie(x,y)=position;
    value++;
  }
  return abs(x) + abs(y);
}

int get_sum_adjacent(const tuple<int,int> &position,
  const map<tuple<int,int>, int> &memory){
    int sum=0;
    const vector<int> directions= {-1,0,1};
    for(int x:directions){
      for(int y:directions){
        int p_x,p_y;
        tie(p_x,p_y)=position;
        auto new_pos=make_tuple(p_x+x,p_y+y);
        auto memory_value=memory.find(new_pos);
        if(memory_value != memory.end()){
          sum+=memory_value->second;
        }
      }
    }
    return sum;
  }

  int part2(int input){
    map<tuple<int,int>, int> memory;
    auto current_position=make_tuple(0,0);
    auto current_position_value=1;
    memory[current_position]=current_position_value;

    do{
      current_position=get_next_position(current_position);
      current_position_value=get_sum_adjacent(current_position,memory);
      memory[current_position]=current_position_value;
    }while(current_position_value<input);

    return current_position_value;
  }

  int main(int argc,char* argv[]){
    if(argc <= 1 ){
      cout << "Usage: day3 input\n";
    }
    else{
      int input=std::atoi(argv[1]);
      cout << "Distance: " << part1(input)  << "\n";
      cout << "Sum: " << part2(input) << "\n";
     }
  }
