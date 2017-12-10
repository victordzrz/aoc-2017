
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include  <iomanip>

using namespace std;


void reverse(vector<char> &input,int positionStart, int lenght);
vector<char> knotHash(const vector<char> &lenghtSequence,int ringLength);

vector<char> knotHash(const vector<char> &lenghtSequence,int ringLength,int nRounds){
  cout << "Starting hash \n"<<flush;
  vector<char> numberList;
  int skipSize=0;
  int currentPosition=0;
  for(int i=0;i<ringLength;i++){
    numberList.push_back(i);
  }

  for(int i=0;i<nRounds;i++){
    //cout << "Round " << i << "\n" << flush;
    for(char length:lenghtSequence){
      reverse(numberList,currentPosition,length);

      //cout << "Result: ";
      // for(auto i:numberList){
      //   cout << i << " ";
      // }
      //cout << "\n______\n";
      currentPosition=(currentPosition+length+skipSize)%ringLength;
      skipSize++;
    }
  }

  vector<char> sparse_hash=numberList;
  vector<char> denseHash;
  for(int j=0;j<16;j++){
    char currentHash=0;
    for(int i=0;i<16;i++){
      currentHash^=sparse_hash[i+16*j];
    }
    denseHash.push_back(currentHash);
    //cout << ((int)j) << ": " << currentHash << "\n";
  }

  return denseHash;
}


void reverse(vector<char> &input,int positionStart, int length){
  vector<char>::iterator first=input.begin()+positionStart;
  vector<char> copy;
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
    //cout << "switching " << *first << " for " << *copy_it << "\n";
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
    /*for(auto it=inputString.begin();it!=inputString.end();it++){
      if(*it==','){
        *it=' ';
      }
    }
    stringstream inputStream(inputString);

    */

    cout << inputString <<"\n" ;

    vector<char> numberList;
    for(char c : inputString){
      numberList.push_back(c);
    }

    vector<char> extra_seq{17,31,73,47,23};

    numberList.insert(numberList.end(),extra_seq.begin(),extra_seq.end());


    // for(char i:numberList){
    //   cout << hex << i << "\n";
    // }

    vector<char> res=knotHash(numberList,256,64);

    for(int c:res){
      cout << hex << std::setw(2) << std::setfill('0') << (c&0x000000ff);
    }
    cout <<  "\n";
  }
}
