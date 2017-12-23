#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <set>
#include <tuple>
#include <fstream>

using namespace std;

tuple<int,set<int>> get_pipe(const string &line);
set<int> build_program_set(map<int,set<int>> pipes,int start);
int get_number_of_groups(map<int,set<int>> pipes);

int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " inputFile\n";
    }else{
        map<int,set<int>> pipes;
        ifstream inputFile(argv[1]);
        string inputString;
        getline(inputFile,inputString);
        while(inputString.size()>0){
            int origin;
            set<int> destinations;
            tie(origin,destinations)=get_pipe(inputString);
            getline(inputFile,inputString);
            pipes[origin]=destinations;
        }

        auto final_set=build_program_set(pipes,0);
        cout << "size of group 0: " << final_set.size() << "\n"; 
        cout << "number of groups: " << get_number_of_groups(pipes) << "\n";
    }
    cout << flush;
    return 0;
}

tuple<int,set<int>> get_pipe(const string &line){
    regex origin_regex("([0-9]+) <-> ");
    regex dest_regex("([0-9]+),?");
    smatch base_match;

    regex_search(line,base_match,origin_regex);
    int origin=stoi(base_match[1].str());
    //cout << "O: "  << origin << "\n";

    auto search_start=line.cbegin()+base_match.position()+base_match.length();
    set<int> destinations;
    while( regex_search(search_start,line.cend(),base_match,dest_regex)){
        search_start += base_match.position() + base_match.length();

        for(int index=1; index<base_match.size(); index++){
            destinations.insert(stoi(base_match[index].str()));
            //cout << " -> " << base_match[index].str() << "\n";
        }
    }

    return make_tuple(origin,destinations);
}

set<int> build_program_set(map<int,set<int>> pipes, int start){
    set<int> result;
    set<int> new_programs;
    
    new_programs.insert(start);

    while(new_programs.size()>0){
        auto it=new_programs.begin();
        for(auto program:pipes[*it]){
            auto insert_result=result.insert(program);
            if(insert_result.second)//inserted successfully
            {
                new_programs.insert(program);
            }
        }
        new_programs.erase(it);
    }

    return result;
}

int get_number_of_groups(map<int,set<int>> pipes){
    set<int> already_grouped;
    int number_of_groups=0;

    for(auto pipe:pipes){
        auto origin=pipe.first;
        auto is_not_grouped=already_grouped.insert(origin).second;
        if(is_not_grouped){
            auto new_group= build_program_set(pipes,origin);
            for(auto program:new_group){
                already_grouped.insert(program);
            }
            number_of_groups++;
        }
    }

    return number_of_groups;
}