// Example program
#include <iostream>
#include <string>
#include <set>
#include <sstream>
#include <map>

using namespace std;

bool is_valid_passphrase1(const string &passphrase);
bool is_valid_passphrase2(const string &passphrase);

int main()
{
  string line;
  getline(std::cin,line);
  auto correct1=0;
  auto correct2=0;
  while(line.size()>0){
      if(is_valid_passphrase1(line)){
        correct1++;
      }
      if(is_valid_passphrase2(line)){
        correct2++;
      }
      getline(std::cin,line);
  }
  cout << correct1 << '\n';
  cout << correct2 << '\n';
}

bool is_valid_passphrase1(const string &passphrase){
    set<string> word_set;
    stringstream phrase(passphrase);
    string word;
    
    while(phrase >> word){
        auto result=word_set.insert(word);
        if(!result.second){
            return false;
        }
    }
    
    return true;
}

bool is_valid_passphrase2(const string &passphrase){
    set<map<char,int>> word_set;
    stringstream phrase(passphrase);
    string word;
    
    while(phrase >> word){
        map<char,int> char_map;
        for(char c:word){
            char_map[c]=char_map[c]++;
        }
        auto result=word_set.insert(char_map);
        if(!result.second){
            return false;
        }
    }
    
    return true;
}