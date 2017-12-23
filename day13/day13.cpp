#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <regex>
#include <set>
#include <tuple>
#include <fstream>

using namespace std;

int position_at_step(int step, int range);
int severity_with_delay(int delay,map<int,int> &firewall);
bool caught_with_delay(int delay,map<int,int> &firewall);

int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " inputFile\n";
    }else{
        map<int,int> firewall;
        ifstream inputFile(argv[1]);
        string inputString;
        getline(inputFile,inputString);
        regex firewall_regex("([0-9]+): ([0-9]+)");

        smatch base_match;

        while(inputString.size()>0){
            int layer,range;
            
            regex_search(inputString,base_match,firewall_regex);

            if(base_match.size() > 2){
                layer=stoi(base_match[1]);
                range=stoi(base_match[2]);
                cout << "Layer: " << layer << "\n";
                cout << "Range: " << range << "\n";
            }

            getline(inputFile,inputString);
            firewall[layer]=range;
        }

        cout << "Severity with delay 0: " << severity_with_delay(0,firewall) << "\n";
        int delay=0;
        while(caught_with_delay(delay,firewall)){
            delay++;
        }
        cout << "Delay of success: " << delay << "\n";
    }
    return 0;
}

int position_at_step(int step, int range){
    int sub_range=range-1;
    int sub_step=step % (sub_range*2);
    int rounds=(sub_step)/sub_range;
    if(rounds % 2 == 0){//going
        return sub_step % sub_range;
    }
    else{//coming
        return sub_range - (sub_step % sub_range);
    }
}

int severity_with_delay(int delay,map<int,int> &firewall){
    int severity=0;
    for(auto layer:firewall){
        int position=position_at_step(layer.first,layer.second);
        //cout << "Layer:"  << layer.first << " Range: " << layer.second << " Position: " << position << "\n"; 
        if(position==0){
            severity+=layer.second*layer.first;
            //cout << "Add\n";
        }
    }
    return severity;
}

bool caught_with_delay(int delay,map<int,int> &firewall){
    int severity=0;
    for(auto layer:firewall){
        int position=position_at_step(layer.first+delay,layer.second);
        //cout << "Layer:"  << layer.first << " Range: " << layer.second << " Position: " << position << "\n"; 
        if(position==0){
            return true;
        }
    }
    return false;
}
