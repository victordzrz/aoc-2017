#include <iostream>
#include <vector>
#include <map>
#include <regex>
#include <fstream>
#include <string>

using namespace std;

class Instruction{
        string ins;
        string arg1;
        string arg2;
    public:
        Instruction(string i, string a1, string a2) :  ins(i), arg1(a1), arg2(a2) {}
        void execute(map<string,long long int> &memory, int &pc, vector<long int> &rcv, vector<long int> &snd,int &send_count){
            cout << ins << " " << arg1 << " " << arg2 << "\n"; 
            if(ins== "snd"){
                snd.push_back(resolve(arg1,memory));
                send_count++;
                pc++;
            }
            else if(ins==  "set"){
                memory[arg1]=resolve(arg2,memory);
                pc++;
            }
            else if(ins==  "add"){
                memory[arg1]=memory[arg1]+resolve(arg2,memory);
                pc++;
            }
            else if(ins== "mul"){
                memory[arg1]=memory[arg1]*resolve(arg2,memory);
                pc++;
            }
            else if(ins=="mod"){
                memory[arg1]=memory[arg1] % resolve(arg2,memory);
                pc++;
            }
            else if(ins== "rcv"){
                if(rcv.size()>0){
                    memory[arg1]=*rcv.begin();
                    rcv.erase(rcv.begin());
                    pc++;
                }
            }
            else if(ins=="jgz"){
                if(resolve(arg1,memory)>0){
                    pc+=resolve(arg2,memory);
                }
                else{
                    pc++;
                }
            }
            else{
                cout << "oops\n";
                pc++;
            }
        }
    private:
        long long int resolve(string s,map<string,long long int> memory){
            if((s[0]>='0' && s[0]<='9' ) || s[0]=='-' ){
                long long int resolved=stoi(s);
                return resolved;
            }else{
                long long int resolved=memory[s];
                return resolved;
            }
        }
};

void print_memory(map<string,long long int> memory){
    for(auto m:memory){
        cout << m.first << "[" << m.second <<"] ";
    }

    cout << "\n";
}

int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " input\n";
    }else{
        vector<Instruction> program;
        ifstream inputFile(argv[1]);
        string inputString;
        getline(inputFile,inputString);
        while(inputString.size()>0){
            cout << inputString << "\n";

            regex instruction_regex("([a-z]+) ([a-z0-9-]+)[ ]*([a-z0-9-]*)");

            smatch ins_match;

            if(regex_search(inputString,ins_match,instruction_regex)){
                cout << "Matched (" << ins_match[1]  << ") (" << ins_match[2] << ")";
                if (ins_match.size()>3){
                    cout << " (" << ins_match[3] << ")";
                }
                cout << "\n";
                program.push_back(Instruction(ins_match[1],ins_match[2],ins_match[3]));
            }
            getline(inputFile,inputString);
        }

        map<string,long long int> memory0;
        memory0["p"]=0;
        map<string,long long int> memory1;
        memory1["p"]=1;
        int previous_pc0=0;
        int previous_pc1=0;
        int pc0=0;
        int pc1=0;
        vector<long int> msg0;
        vector<long int> msg1;
        bool stuck=false;
        int send_count1=0;
        int send_count0=0;

        while((pc0 < program.size() || pc1 < program.size()) && !stuck){
            previous_pc0=pc0;
            previous_pc1=pc1;
            program[pc0].execute(memory0,pc0,msg1,msg0,send_count0);
            program[pc1].execute(memory1,pc1,msg0,msg1,send_count1);
            //cout << "PC: " << pc << " S: " << sound << "\n";
            //print_memory(memory);
            //cout << "\n";
            if(previous_pc0==pc0 && previous_pc1==pc1){
                //stuck=true;
                stuck=true;
                cout << "Stuck!"<< "\n";
                cout << "Send count 1: " << send_count1 << "\n";
            }
        }
    }
    return 0;
}