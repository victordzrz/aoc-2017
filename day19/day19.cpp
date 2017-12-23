#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <fstream>

using namespace std;

tuple<int,int> findStart(vector<string> inputMap);
tuple<int,int> nextPosition(tuple<int,int> pos,tuple<int,int> previous_pos,vector<string> inputMap);
char getAt(tuple<int,int> pos,vector<string> inputMap);

int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " input\n";
    }else{
        vector<string> inputMap;
        ifstream inputFile(argv[1]);
        string inputString;
        getline(inputFile,inputString);
        while(inputString.size()>0){
            inputMap.push_back(inputString);
            getline(inputFile,inputString);
        }

        int x,y;
        auto pos=findStart(inputMap);
        tie(x,y)=pos;
        int previous_x=x;
        int previous_y=y-1;
        char c=getAt(pos,inputMap);
        auto previous_pos=make_tuple(previous_x,previous_y);
        int steps=0;
        while(c!=' '){
            if(c>='A' && c<='Z'){
                cout << c;
            }else{
                //cout << c;
            }

            tie(x,y)=pos;
            //cout << " (" << x << "," << y << ")" << "\n";
            
            auto new_pos=nextPosition(pos,previous_pos,inputMap);
            previous_pos=pos;
            pos=new_pos;
            c=getAt(pos,inputMap);
            steps++;
        }
        cout << "\n";
        cout << "Steps: " << steps << "\n";
    }
    return 0;
}

tuple<int,int> findStart(vector<string> inputMap){
    int y=0;
    for(auto line:inputMap){
        int x=0;
        for(auto c:line){
            if(c=='|'){
                return make_tuple(x,y);
            }
            x++;
        }
        y++;
    }
    return make_tuple(-1,-1);
}

tuple<int,int> nextPosition(tuple<int,int> pos,tuple<int,int> prevPos,vector<string> inputMap){
    int x_pos,y_pos;
    int x_prev,y_prev;
    int x_dir,y_dir;

    tie(x_pos,y_pos)=pos;
    tie(x_prev,y_prev)=prevPos;
    x_dir=x_pos-x_prev;
    y_dir=y_pos-y_prev;
    

    if(getAt(pos,inputMap) == '+'){
        for(auto new_x_dir:{-1,0,1}){
            for(auto new_y_dir:{-1,0,1}){
                if((new_x_dir!=0 || new_y_dir!=0)){
                    auto new_pos=make_tuple(x_pos+new_x_dir,y_pos+new_y_dir);
                    if(new_pos!=prevPos){
                        if(getAt(new_pos,inputMap)!=' '){
                            return new_pos;
                        }
                    }
                }
            }   
        }
    }
    else{
        return make_tuple(x_dir+x_pos,y_dir+y_pos);
    }
}

char getAt(tuple<int,int> pos,vector<string> inputMap){
    int x,y;
    tie(x,y)=pos;
    if(y<inputMap.size() && x<inputMap[0].size() && y>=0 && y>=0){
        //cout << "r " << inputMap[y][x];  
        return inputMap[y][x];
    }
    else{
        //cout << "?";
        return ' ';
    }
}
