#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <map>

using namespace std;

enum class Direction{
    N=0,
    NE,
    SE,
    S,
    SW,
    NW,
    Stay,
    None
};

Direction stringToDirection(const string &s){
    if(s == "n")
        return Direction::N;
    else if(s=="nw")
        return Direction::NW;
    else if(s=="ne")
        return Direction::NE;
    else if(s=="s")
        return Direction::S;
    else if(s=="se")
        return Direction::SE;
    else if(s=="sw")
        return Direction::SW;
    else
        return Direction::None;
}

string directionToString(const Direction &d){
    if(d == Direction::N)
        return "n";
    else if(d==Direction::NW)
        return "nw";
    else if(d == Direction::NE)
        return "ne";
    else if(d == Direction::S)
        return "s";
    else if(d == Direction::SE)
        return "se";
    else if(d == Direction::SW)
        return "sw";
    else if(d == Direction::Stay)
        return "stay";
    else
        return ".";
}

Direction getOpposite(const Direction &d){
    return Direction((static_cast<int>(d)+3)%6);
}

bool areOpposite(const Direction &d1,const Direction &d2){
    return abs(static_cast<int>(d1)-static_cast<int>(d2))==3;
}


Direction combine(const Direction &d1,const Direction &d2){
    if(areOpposite(d1,d2)){
        return Direction::Stay;
    }
    int d1Value=static_cast<int>(d1);
    int d2Value=static_cast<int>(d2);
    int distance=abs(d1Value-d2Value);
    if(distance==2){
        return Direction(max(d1Value,d2Value)-1);
    }
    else{
        if(distance==4){
            return Direction((max(d1Value,d2Value)+1)%6);
        }
    }
    return Direction::None;
}

vector<Direction> reduce(const vector<Direction> &dirVec){
    map<Direction,int> dirCountMap;
    for(Direction d:dirVec){
        Direction opposite=getOpposite(d);
        if(dirCountMap[opposite]>0){
            dirCountMap[opposite]--;
        }else{
            Direction combined=Direction::None;
            Direction combination=Direction::None;
            for(auto dirCount:dirCountMap){
                if(dirCount.second>0){
                    combined=combine(dirCount.first,d);
                    if(combined!=Direction::None){//not possible to combine
                        combination=dirCount.first;
                        break;
                    }
                }
            }
            if(combined==Direction::None){
                dirCountMap[d]++;
            }else{
                dirCountMap[combination]--;
                if(combined!=Direction::Stay){
                    dirCountMap[combined]++;
                }
            }
        }
    }

    vector<Direction> result;
    for(auto dirCount:dirCountMap){
        for(int i=0;i<dirCount.second;i++){
            result.push_back(dirCount.first);
        }
    }

    return result;
}


int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " inputFile\n";
    }else{
    ifstream inputFile(argv[1]);
    string inputString;
    getline(inputFile,inputString);
    cout << "Input:\n";
    cout << inputString << "\n";
    for(auto it=inputString.begin();it!=inputString.end();it++){
      if(*it==','){
        *it=' ';
      }
    }
    stringstream inputStream(inputString);
    string direction;

    vector<Direction> directionVec;

    unsigned int max_distance=0;

    while(inputStream >> direction){
            directionVec.push_back(stringToDirection(direction));
            max_distance=max(max_distance,(unsigned int)reduce(directionVec).size());
    }

    for(auto d:directionVec){
        //cout << directionToString(d)  << "\n";
    }

    vector<Direction> allDirs={Direction::N,Direction::NE,Direction::NW,Direction::S,Direction::SW,Direction::SE};

    // for(auto d1:allDirs){
    //     for(auto d2:allDirs){
    //         cout << directionToString(d1) << " + " << directionToString(d2)  << " = " << directionToString(combine(d1,d2)) << "\n";
    //     }
    // }

    auto result=reduce(directionVec);
    cout << "Shortest distance: " << result.size() << "\n";
    cout << "Maximum disctance: " << max_distance << "\n";
}
}
