#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char* argv[]){
    if(argc < 1){
        cout << "Usage: " << argv[0] << " input\n";
    }else{
        int stepSize=stoi(argv[1]);

        vector<long int> circularBuffer {0L};
        
        int currentPos=0;
        int size=1;

        for(long int i=1L;i<=50000000L;i++){
            currentPos=((currentPos+stepSize)%size)+1;
            if(currentPos==1){
                circularBuffer.insert(circularBuffer.cbegin()+currentPos,i);
            }
            size++;
            if(i%10000==0){
                cout << i << "\n";
                cout << flush;
            }
        }
        cout << circularBuffer[1] << "\n";
    }
    return 0;
}