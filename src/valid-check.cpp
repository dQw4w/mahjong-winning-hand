#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include<algorithm>
#define ll long long

using namespace std;

void help_message() {
    cout << "usage: valid-checker <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]) {///adsdad
    if (argc != 3) {
        help_message();
        return 0;
    }

 
    //////////// read the input file /////////////qsqsqqsq
    fstream fin1(argv[1]); // Open the input filessssssqqqqefqsaaaaasdassadsadsdadadasssswww
    if (!fin1.is_open()) {
        cout << "Error: Unable to open input file." << endl;
        return 1;
    }

    

    int num;
    int verticeNum;

    fin1 >> verticeNum;
   
    int count = 0;
    int num1, num2;
    vector<int> chordList;
    chordList.assign(verticeNum,-1);
    while (fin1 >> num){
        count++;
        if (count % 2 == 1){
            num1 = num;
        }else{
            num2 = num;
            if (num1 < num2){
                chordList[num1] = num2;
            }else{
                chordList[num2] = num1;
            }
        }
        
    }
    fstream fin2(argv[2]); 
    if (!fin2.is_open()) {
        cout << "Error: Unable to open input file." << endl;
        return 1;
    }
    
    int mps;
    fin2 >> mps;
    vector<pair<int,int>> outputList;
    count = 0;
    while (fin2 >> num){
        count++;
        if (count % 2 == 1){
            num1 = num;
        }else{
            num2 = num;
            outputList.push_back(make_pair(num1,num2));
        }   
    }
    if (count/2 != mps){

        cout << "number of chords invalid" << endl;
        cout << "count = " << count << endl;
        cout << "mps = " << mps << endl;
        return 0;
    }
    int prevFirst = -1;
    for (int i = 0; i < outputList.size();i++){
        int firstPoint = outputList[i].first;
        int secondPoint = outputList[i].second;
        if (firstPoint <= prevFirst){
            cout << "not sorted in order" << endl;
            return 0;
        }
        if (chordList[firstPoint] != secondPoint){
            cout << "output chord not in input" << endl;
            return 0;
        }
    }
    for (int i = 0; i < outputList.size();i++){
        int a1 = outputList[i].first;
        int a2 = outputList[i].second;
        for (int j = 0; j < outputList.size();j++){
            if (j == i){
                continue;
            }
            int b1 = outputList[j].first;
            int b2 = outputList[j].second;
            if (a1 < b1 && a2 < b2 && b1 < a2){
                cout << "overlap" << endl;
                return 0;
            }
        } 
    }
    cout << "valid" << endl;
    fin1.close();
    fin2.close();
    return 0;
}
