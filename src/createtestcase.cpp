#include<iostream>
#include <fstream>

using namespace std;

int main(){
    fstream fout;
    fout.open("haha.out", ios::out);
    if (!fout.is_open()) {
        cout << "Error: Unable to open output file." << endl;
        return 1;
    }
    fout << 999998 << endl;
   for (int i= 1; i < 333334; i++){
    fout << i << endl << i << endl << i << endl;
   }
   fout.close();
   return 0;
}