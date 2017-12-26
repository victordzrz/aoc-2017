#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <regex>
#include <algorithm>
#include <set>
#include <cmath>

using namespace std;

void print_component(const tuple<int,int> &comp);
void print_bridge(const set<int>&,const vector<tuple<int,int>>&);
vector<tuple<set<int>,int>> init_bridge_list(const vector<tuple<int,int>> &);
vector<tuple<set<int>,int>> extend_bridge(const tuple<set<int>,int> &bridge,vector<tuple<int,int>> &componentList);
int calculate_bridge_strength(const set<int> &bridge,const vector<tuple<int,int>> components);


int main(int argc, char * argv[]){
  if(argc < 1){
    cout << "Usage: " << argv[0] << " inputFile\n";
  }else{
    ifstream inputFile(argv[1]);
    std::string inputString;

    vector<tuple<int,int>> componentList;
    vector<tuple<set<int>,int>> bridgeList;

    getline(inputFile,inputString);
    while(inputString.size()>0){

      regex compRegex("([0-9]+)/([0-9]+)");

      smatch match;

      if(regex_search(inputString,match,compRegex)){
        componentList.push_back(make_tuple(stoi(match[1]),stoi(match[2])));
      }
      getline(inputFile,inputString);
    }

    bridgeList=init_bridge_list(componentList);

    for(auto comp:componentList){
      print_component(comp);
      cout << "\n";
    }

    int max_strength=0;
    set<int> max_bridge;
    size_t max_lenght=0;
    int max_lenght_strength=0;

    while(bridgeList.size()>0){
        tuple<set<int>,int> currentBridge=bridgeList.back();

        vector<tuple<set<int>,int>> newBridges=extend_bridge(currentBridge,componentList);
        if(newBridges.size()>0){

          bridgeList.pop_back();
          for(auto b:newBridges){
            bridgeList.push_back(b);
          }
        }else{
          set<int> bridge;
          tie(bridge,ignore)=currentBridge;
          int new_s=calculate_bridge_strength(bridge,componentList);
          if(new_s>max_strength){
            max_strength=new_s;
            cout << "Max " << max_strength << "\n";
            max_bridge=bridge;
          }
          if(bridge.size()>max_lenght){
            max_lenght=bridge.size();
            max_lenght_strength=new_s;
          }else if(bridge.size()==max_lenght && new_s>max_lenght_strength){
            max_lenght_strength=new_s;
          }
          bridgeList.pop_back();
        }
    }

    cout << "Max strength: " << max_strength <<"\n";
    cout << "Max lenght " << max_lenght << " and max strength " << max_lenght_strength << "\n";

  }
  return 0;
}

int calculate_bridge_strength(const set<int> &bridge,const vector<tuple<int,int>> components){
  int strength=0;
  for(int i:bridge){
    int p1,p2;
    tie(p1,p2)=components[i];
    strength+=p1+p2;
  }
  return strength;
}


void print_component(const tuple<int,int> &comp){
  int p1,p2;
  tie(p1,p2)=comp;

  cout << p1 << "/" << p2;
}

void print_bridge(const set<int>& bridge,const vector<tuple<int,int>>& components){
  for(auto i:bridge){
    cout << "("<<i<<")";
    print_component(components[i]);
    cout << ",";
  }

  cout << "\n";
}


vector<tuple<set<int>,int>> init_bridge_list(const vector<tuple<int,int>> &componentList){
  vector<tuple<set<int>,int>> bridgeList;

  for(size_t i=0;i<componentList.size();i++){
    int p1,p2;
    tie(p1,p2)=componentList[i];

    if(p1==0){
      auto usedSet=set<int>();
      usedSet.insert(i);
      bridgeList.push_back(make_tuple(usedSet,p2));
    }
    else if(p2==0){
      auto usedSet=set<int>();
      usedSet.insert(i);
      bridgeList.push_back(make_tuple(usedSet,p1));
    }
  }
  return bridgeList;
}

vector<tuple<set<int>,int>> extend_bridge(const tuple<set<int>,int> &bridge,
  vector<tuple<int,int>> &componentList){
    vector<tuple<set<int>,int>> newBridges;
    set<int> usedInBridge;
    int nextPort;
    tie(usedInBridge,nextPort)=bridge;

    for(size_t i=0;i<componentList.size(); i++){
      if(usedInBridge.find(i)==usedInBridge.end()){
        int p1,p2;
        tie(p1,p2)=componentList[i];
        if(p1==nextPort){
          int newNextPort=p2;
          set<int> newSet(usedInBridge);
          newSet.insert(i);
          newBridges.push_back(make_tuple(newSet,newNextPort));
        }
        else if(p2==nextPort){
          int newNextPort=p1;
          set<int> newSet(usedInBridge);
          newSet.insert(i);
          newBridges.push_back(make_tuple(newSet,newNextPort));
        }
      }
    }
    return newBridges;
}
