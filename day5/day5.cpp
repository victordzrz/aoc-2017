#include <iostream>
#include <string>
#include <vector>

using namespace std;

long int traverse_maze(vector<int> &maze, int start_position);

int main(int argc, char* argv[]){
    vector<int> maze;
    int current_position;
    string line;
    getline(cin,line);
    while(line.size()>0){
        
        cout << line << '\n';
        if(line.front()=='(' && line.back()==')'){
            line=line.substr(1,line.size()-2);
            current_position=stoi(line);
        }
        maze.push_back(stoi(line));
        getline(cin,line);
    }
    cout << "Maze:" << "\n";

    cout << "Steps to exit: " << traverse_maze(maze,0) << "\n";
}

long int traverse_maze(vector<int> &maze, int position){
    long int step_count=0;
    cout << "Starting traverse at " << position << '\n';
    
    while(position>=0 && position < maze.size()){
        int previous_position=position;
        //cout << position << " " << maze[position] << " = ";
        position+=maze[position];
        //cout << position << "\n";
        if(position-previous_position>=3){
            maze[previous_position]--;
        }else{
            maze[previous_position]++;
        }
        //cout << "Change to " << maze[previous_position] << "\n";
        step_count++;
    }
    return step_count;
}