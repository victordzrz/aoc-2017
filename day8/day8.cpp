#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <regex>
#include <set>
#include <fstream>

using namespace std;

class Instruction {
    public:
        string reg,ins,lcond,op;
        int ammount,rcond;  
        bool condition(int lcond_value){
            if(op=="=="){
                return lcond_value==rcond;
            }
            if(op=="<"){
                return lcond_value<rcond;
            }
            if(op=="<="){
                return lcond_value<=rcond;
            }
            if(op==">"){
                return lcond_value>rcond;
            }
            if(op==">="){
                return lcond_value>=rcond;
            }
            if(op=="!="){
                return lcond_value!=rcond;
            }
        }

        bool evaluate(map<string,int> &memory){
            int reg_value=memory[reg];
            int lcond_value=memory[lcond];
            if(condition(lcond_value))
            {
                if(ins=="dec"){
                    //cout << "+";
                    memory[reg]-=ammount;
                    cout << reg << "-" << ammount << "=" << memory[reg] <<"\n";
                    return true;
                }
                if(ins=="inc"){
                    //cout << "-";
                    memory[reg]+=ammount;
                    cout << reg << "+" << ammount << "=" << memory[reg] << "\n";
                    return true;
                }
                cout << "error\n";
                return false;
            }  
            //cout << "0";
            return true;
        }  
};





int main(int argc, char* argv[]){
    if(argc >1){
        ifstream input(argv[1]);
        if(input.is_open()){
            map<string,int> memory;
            string line;
            getline(input,line);
            int max=0;
            string smax;
            while(line.size()>0){
                regex instruction_regex("([a-z]+) ([a-z]+) ([-0-9]+) if ([a-z]+) ([><=!]+) ([-0-9]+)");
                smatch base_match;
                regex_search(line,base_match,instruction_regex);
                Instruction i;
                i.reg=base_match[1];
                i.ins=base_match[2];
                i.ammount=stoi(base_match[3]);
                i.lcond=base_match[4];
                i.op=base_match[5];
                i.rcond=stoi(base_match[6]);
                
                i.evaluate(memory);
                for(auto mem:memory){
                    if(mem.second > max){
                        max=mem.second;
                        smax=mem.first;
                    }
                }
                getline(input,line);  
            }

            
            
            cout << "\n max: " << smax << "=" << max << "\n";
        }
    }
    else{
        cout << "Usage: day8 input.txt\n";
    }
}