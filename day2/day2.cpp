#include <iostream>
#include <string>
#include <sstream>
#include <climits>
#include <vector>

int find_row_checksum2(const std::vector<int>& row){
  for(const int& n1:row){
    for(const int& n2:row){
      int max=0;
      int min=0;
      if(n2 != n1){
        if(n1>n2){
          max=n1;
          min=n2;
        }
        else{
          max=n2;
          min=n1;
        }
        if(max%min ==0 ){
          return max/min;
        }
      }
    }
  }
  return 0;
}

int find_row_checksum1(const std::vector<int>& row){
  int max=INT_MIN;
  int min=INT_MAX;
  for(int next:row){
    if (next > max){
      max=next;
    }
    if(next < min){
      min=next;
    }
  }
  return max-min;
}

int main(){
  std::string line;
  std::string path;
  std::cout << "Enter your spreadsheet:\n";
  int checksum1=0;
  int checksum2=0;
  getline(std::cin,line);
  while(line.size()>0){
    std::stringstream ss(line);
    std::vector<int> row_numbers;
    int next=0;
    while(ss >> next){
      row_numbers.push_back(next);
    }
    checksum1+=find_row_checksum1(row_numbers);
    checksum2+=find_row_checksum2(row_numbers);
    getline(std::cin,line);
  }

  std::cout << "Spreadsheet checksum1: " << checksum1 << '\n';
  std::cout << "Spreadsheet checksum2: " << checksum2 << '\n';
}
