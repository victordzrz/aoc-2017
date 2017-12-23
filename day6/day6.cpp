#include <iostream>
#include <vector>
#include <set>
#include <sstream>
#include <algorithm>

using namespace std;

void print_config(vector<int> &config){
    for(int i:config){
        cout << i <<"  ";
    }
    cout << "\n";
}

int main(int argc, char* argv[]){
    vector<int> memory_blocks;
    int next_block;
    string line;
    getline(cin,line);
    stringstream lineStream(line);
    while(lineStream >> next_block){
        memory_blocks.push_back(next_block);
    }

    print_config(memory_blocks);

    set<vector<int>> configurations;
    vector<int> current_configuration=memory_blocks;
    vector<vector<int>> configurations_list;//to calculate the loop lenghts, quite dirty
    auto result=configurations.insert(current_configuration);
    configurations_list.push_back(current_configuration);
    
    do{
      vector<int>::iterator element=max_element(current_configuration.begin(),current_configuration.end());
      int index=distance(current_configuration.begin(),element);
      int to_balance=*element;
      current_configuration[index]=0;
      while(to_balance>0){
          index=(index+1)%current_configuration.size();
          current_configuration[index]++;
          to_balance--;
      }
      result=configurations.insert(current_configuration);
      configurations_list.push_back(current_configuration);
      print_config(current_configuration);
    }while(result.second);

    cout << "Cycles set: " << configurations.size() << "\n";
    int index_of_vector=0;
    for(vector<int> cnf:configurations_list){
        if(cnf==current_configuration){
            break;
        }
        index_of_vector++;
    }
    cout << "Loop lenght based on list: " << configurations_list.size()-index_of_vector-1;
}