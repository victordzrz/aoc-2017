
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;


void reverse(vector<int> &input,int positionStart, int lenght);
int knotHash(const vector<int> &lenghtSequence,int ringLength);

int knotHash(const vector<int> &lenghtSequence,int ringLength){
  vector<int> numberList;
  int skipSize=0;
  int currentPosition=0;
  for(int i=0;i<ringLength;i++){
    numberList.push_back(i);
  }

  for(int length:lenghtSequence){
    reverse(numberList,currentPosition,length);

    cout << "Result: ";
    for(auto i:numberList){
      cout << i << " ";
    }
    cout << "\n______\n";
    currentPosition=(currentPosition+length+skipSize)%ringLength;
    skipSize++;
  }

  return numberList[0]*numberList[1];
}


void reverse(vector<int> &input,int positionStart, int length){
  vector<int>::iterator first=input.begin()+positionStart;
  vector<int> copy;
  auto current_it=first;
  for(auto i=0;i<length;i++){
    copy.push_back(*current_it);
    current_it++;
    if(current_it==input.end()){
      current_it=input.begin();
    }
  }

  auto copy_it=copy.end()-1;

  for(auto i=0;i<length;i++){
    cout << "switching " << *first << " for " << *copy_it << "\n";
    *first=*copy_it;
    copy_it--;
    first++;
    if(first==input.end()){
      first=input.begin();
    }
  }
}

int main(int argc,char* argv[]){
  if(argc < 1){
    cout << "Usage: " << argv[0] << " inputFile\n";
  }else{
    ifstream inputFile(argv[1]);
    string inputString;
    getline(inputFile,inputString);
    cout << "Input:\n";
    for(auto it=inputString.begin();it!=inputString.end();it++){
      if(*it==','){
        *it=' ';
      }
    }

    cout << inputString <<"\n" ;

    stringstream inputStream(inputString);
    int num;
    vector<int> numberList;
    while(inputStream >> num){
      numberList.push_back(num);
    }

    for(int i:numberList){
      cout << i << "\n";
    }

    int res=knotHash(numberList,256);

    cout << "Result is: " << res << "\n";
  }
}
