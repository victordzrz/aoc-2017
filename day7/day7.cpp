#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <regex>
#include <set>

using namespace std;

struct Program{
    string name;
    int weight=0;
    int supported_weight=0;
    set<string> supported_programs;
};

Program get_program(const string &line);
void print_program(const Program &p);
Program is_not_supported(const map<string,Program> &program_tree);
bool is_balanced(Program &p,map<string,Program> &program_tree);
int calculate_total_weight( Program &p,  map<string,Program> &program_tree);
bool supported_programs_are_balanced(Program &start, map<string,Program> &program_tree);
bool parent_is_balanced(Program &start, map<string,Program> &program_tree);
Program get_unbalanced_program(Program &start, map<string,Program> &program_tree);
set<string> find_brothers(Program &start,map<string,Program> &program_tree);
Program find_parent(Program &start, map<string,Program> &program_tree);
Program get_program_in_unbalance(Program &start, map<string,Program> &program_tree);

int main(int argc, char* argv[]){
    map<string,Program> program_tree;
    string line;
    getline(cin,line);
    while(line.size()>0){
        Program p=get_program(line);
        //print_program(p);
        program_tree[p.name]=p;
        getline(cin,line);
    }

    Program first=is_not_supported(program_tree);

    cout <<"Not supported: " << first.name << "\n";

    Program unbalanced_prog=get_program_in_unbalance(first,program_tree);

    cout <<"Program in unbalance: " << unbalanced_prog.name << " " << unbalanced_prog.weight << "\n";

    for(auto children:unbalanced_prog.supported_programs){
        cout << children << " " << program_tree[children].supported_weight << "\n";
    }

    cout << "Brothers of unbalanced: "<<"\n";
    
    for(auto brother:find_brothers(unbalanced_prog,program_tree)){
        cout << brother << " " << program_tree[brother].supported_weight;
    }
}

set<string> find_brothers(Program &start, map<string,Program> &program_tree){
    for(auto element:program_tree){
        set<string> children=element.second.supported_programs;
        if(children.find(start.name)!=children.end()){
            return children;
        }
    }
    return set<string>();
}

Program find_parent(Program &start, map<string,Program> &program_tree){
    for(auto element:program_tree){
        set<string> children=element.second.supported_programs;
        if(children.find(start.name)!=children.end()){
            return element.second;
        }
    }
    return Program();
}

//Find an unbalanced program with balanced children.
Program get_unbalanced_program(Program &start, map<string,Program> &program_tree){
    for(auto element:program_tree){
        Program current_program=element.second;
        if(is_balanced(current_program,program_tree)){
            cout << current_program.name << " is balanced." << "\n";
        }else{
            cout << current_program.name << " is unbalanced ";
            if(supported_programs_are_balanced(current_program,program_tree)){
                cout << " and the childrens of " <<  current_program.name << " are balanced." << "\n";
                return current_program;
            }
            else{
                cout << " and the childrens of " <<  current_program.name << " not balanced." << "\n";
            }
        }
    }
    Program null_program;
    return null_program; 
}

//Find balanced program with unbalanced parent.
Program get_program_in_unbalance(Program &start, map<string,Program> &program_tree){
    for(auto element:program_tree){
        Program current_program=element.second;
        if(is_balanced(current_program,program_tree)){
            cout << current_program.name << " is balanced." << "\n";
        }else{
            cout << current_program.name << " is unbalanced ";
            if(parent_is_balanced(current_program,program_tree)){
                cout << " and the parent of " <<  current_program.name << " in balanced." << "\n";
            }
            else{
                cout << " and the parent of " <<  current_program.name << " is not balanced." << "\n";
                return current_program;
            }
        }
    }
    Program null_program;
    return null_program; 
}

bool supported_programs_are_balanced(Program &start, map<string,Program> &program_tree){;
    for(string sub_p:start.supported_programs){
        if(!is_balanced(program_tree[sub_p],program_tree)){
            cout << "Sup: " << sub_p << " is not balanced" << "\n";
            return false;
        }else{
            cout << "Sup: " << sub_p << " is balanced" << "\n";
        }
    }
    return true;
}

bool parent_is_balanced(Program &start, map<string,Program> &program_tree){
    Program parent=find_parent(start,program_tree);
    return is_balanced(parent,program_tree);
}

bool is_balanced(Program &p, map<string,Program> &program_tree){
    cout << p.name << " Is balanced\n";
    int last_weight=-1;
    int new_weight;
    for(string sub_p:p.supported_programs){
        new_weight=calculate_total_weight(program_tree[sub_p],program_tree);
        if(last_weight>0){
            if(new_weight!=last_weight){
                return false;
            }
        }
        last_weight=new_weight;
    }
    return true;
}

int calculate_total_weight( Program &p, map<string,Program> &program_tree){
    if(p.supported_weight==0){
        p.supported_weight=p.weight;

        for(string sub_p:p.supported_programs){
            p.supported_weight+=calculate_total_weight(program_tree[sub_p],program_tree);
        }
    }
   
    cout << "Total weight of " << p.name << " "  << p.supported_weight << "\n";
    return p.supported_weight;
}


Program is_not_supported(const map<string,Program> &program_tree){
    for(auto const p:program_tree){
        bool program_supported=false;
        for(auto const p2:program_tree){
            if(p2.second.supported_programs.find(p.first)!=p2.second.supported_programs.end()){
                program_supported=true;
                cout << p.first << " is supported by " << p2.second.name << "\n";
                break;
            }
        }
        if(!program_supported){
            return p.second;
        }
    }
    Program null_program;
    return null_program;
}


void print_program(const Program &p){
    cout << "Got: " << p.name << " w " << p.weight << " supports ";
        for(string s:p.supported_programs){
            cout << s << ",";
        }
    cout << "\n";
}

Program get_program(const string &line){
    regex name_regex("([a-z]+) \\(");
    regex weight_regex("\\(([0-9]+)\\)");
    regex supported_regex("([a-z]+),?");
    smatch base_match;

    Program new_program;

    regex_search(line,base_match,name_regex);
    new_program.name=base_match[1].str();

    regex_search(line,base_match,weight_regex);
    new_program.weight=stoi(base_match[1].str());

    auto search_start=line.cbegin();
    bool first_match=true;
    while( regex_search(search_start,line.cend(),base_match,supported_regex)){
        search_start += base_match.position() + base_match.length();
        if(first_match){
            first_match=false;
            continue;//skip first
        }
        for(int index=1; index<base_match.size(); index++){
            new_program.supported_programs.insert(base_match[index].str());
        }
    }

    return new_program;
}