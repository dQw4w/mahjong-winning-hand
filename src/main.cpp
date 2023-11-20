
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include<algorithm>
#include "../lib/tm_usage.h"
#include <stdlib.h>
#include <map>

#define ll long long

using namespace std;

bool isWinningHand(int tileCount, map<int,int>tileMap){
    for (const auto& pair : tileMap) {
        if (pair.second >= 2){
            auto copiedMap = tileMap;
            copiedMap[pair.first] -= 2;
            int remainingIterations = (tileCount - 2)/3;
            for (auto it = copiedMap.begin(); it != copiedMap.end(); ++it) {
                int idx = it->first;
                while (it->second > 0){
                    if (it->second >= 3){
                        it->second -= 3;
                        remainingIterations--;
                        continue;
                    }
                    if (copiedMap[idx] && copiedMap[idx+1] && copiedMap[idx+2]){
                        copiedMap[idx] --; 
                        copiedMap[idx+1] --; 
                        copiedMap[idx+2] -- ;
                        remainingIterations--;
                        continue;
                    }
                    break;  
                }
                if (remainingIterations == 0){
                    return true;
                }
            }
        }
    }
    return false;
}

void help_message() {
    cout << "usage: mps <input_file> <output_file>" << endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        help_message();
        return 0;
    }

    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;
    fstream fin(argv[1]); // Open the input files
    if (!fin.is_open()) {
        cout << "Error: Unable to open input file." << endl;
        return 1;
    }

    
    tmusg.periodStart();

    int tileCount;

    // Read the number of vertices
    fin >> tileCount;
    
    map<int,int> tileMap;
    int num;
    while (fin >> num){
        tileMap[num] += 1; 
    }

    if (tileCount % 3 != 2){
        cout << "No" << endl;
    }else if (isWinningHand(tileCount, tileMap)){
        cout << "Yes" << endl;
        // return 0;
    }else{
    cout << "No" << endl;
    }
    
    tmusg.getPeriodUsage(stat);

    cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout << "memory: " << stat.vmPeak << "KB" << endl; // Print peak memoss

 

    fin.close();
    return 0;
}
