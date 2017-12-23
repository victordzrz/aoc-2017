#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <set>
#include <tuple>
#include <fstream>
#include <functional>

using namespace std;


void spin(vector<char> &input, int position);
void exchange(vector<char> &input,int p1,int p2);
void partner(vector<char> &input, char p1,char p2);
void run(vector<char> &input,vector<function<void(vector<char>&)>> &exe_vec);

int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " inputFile\n";
    }else{
        ifstream inputFile(argv[1]);
        string inputString;
        getline(inputFile,inputString);
        regex spin_regex("s([0-9]+)");
        regex exchange_regex("x([0-9]+)/([0-9]+)");
        regex partner_regex("p([a-p])/([a-p])");

        smatch base_match;

        inputString.cbegin();

        for(auto it=inputString.begin();it!=inputString.end();it++){
            if(*it==','){
                *it=' ';
            }
        }

        cout << inputString << "\n";

        stringstream inputStream(inputString);
        string new_command;
        vector<char> start{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
        vector<function<void(vector<char>&)>> execution;
        while(inputStream >> new_command){
            if(regex_search(new_command,base_match,spin_regex)){
                int p=stoi(base_match[1]);
                execution.push_back([p](vector<char> &input){spin(input,p);});
            }
            else if(regex_search(new_command,base_match,exchange_regex)){
                int p1=stoi(base_match[1]);
                int p2=stoi(base_match[2]);
                execution.push_back([p1,p2](vector<char> &input){exchange(input,p1,p2);});
            }
            else if(regex_search(new_command,base_match,partner_regex)){
                char c1=base_match[1].str().at(0);
                char c2=base_match[2].str().at(0);
                execution.push_back([c1,c2](vector<char> &input){partner(input,c1,c2);});
            }else{
                cout << new_command << " oops\n";
            }
        }

        run(start,execution);
        cout << "Final result:\n";
        for(auto c:start){
            cout << c;
        }
        cout << "\n";
        cout << flush;

        vector<char> original{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p'};
        start=original;
        int cycle_size;
        for(long int i=0;i<1000000000L;i++){//1000000000
            run(start,execution);
            if(i%100==0){
                cout << i << "\n";
                cout << flush;
            }
            if(start == original){
                cout << "Back to original after " << i << "\n";
                cout << flush;
                cycle_size=i+1;
                break;
            }
        }

        int billion_eq=1000000000L % cycle_size;

        cout << billion_eq << "\n";
        cout << flush;

        start=original;

        for(int i=0;i<billion_eq;i++){
            run(start,execution);
            cout << i << "\n";
            cout << flush;
        }

        cout << "Final result after 1 billion:\n";
        for(auto c:start){
            cout << c;
        }

        cout << "\n";
        cout << flush;
    }
    return 0;
}

void spin(vector<char> &input, int position){
    //cout << "Spin\n";
    for(int i=0;i<position;i++){
        char last=input.back();
        input.pop_back();
        input.insert(input.begin(),last);
    }
}
void exchange(vector<char> &input,int p1,int p2){
    //cout << "Exchange\n";
    char p1_char=input[p1];
    input[p1]=input[p2];
    input[p2]=p1_char;
}

void partner(vector<char> &input, char p1,char p2){
    //cout << "Partner\n";

    for(auto it=input.begin();it!=input.end();it++){
        if(*it==p1){
            *it=p2;
        }
        else if(*it==p2){
            *it=p1;
        }
    }
}

void run(vector<char> &input,vector<function<void(vector<char>&)>> &exe_vec){
    for(auto f:exe_vec){
        f(input);
    }
}