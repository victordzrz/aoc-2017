#include <iostream>
#include <string>

int main(int argc, char* argv[]){
  if(argc <= 1){
    std::cout << "Use: day1-1 [captcha]\n";
  }
  else{
    auto captcha_string=std::string(argv[1]);
    auto captcha_size= captcha_string.size();
    unsigned long sum1=0,sum2=0;
    for(unsigned long index=0;index<captcha_size;index++){
        if(captcha_string[index]==captcha_string[(index+1)%captcha_size]){
          sum1+=captcha_string[index]-'0';
        }
        if(captcha_string[index]==captcha_string[(index+(captcha_size/2))%captcha_size]){
          sum2+=captcha_string[index]-'0';
        }
    }
    std::cout << "Captcha 1:" << sum1 << '\n';
    std::cout << "Captcha 2:" << sum2 << '\n';
  }
}
