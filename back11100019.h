#include <vector>
#include <utility>
#include<iostream>
#include <set>
#include <algorithm>
using namespace std;


vector<int> chordList;
vector<vector<int>> M;


void init(int endPoints){
    for (int i = 0; i < endPoints; i++){
        M.push_back({});
        for (int j = 0; j < endPoints - i; j++){
            M[i].push_back(-1);//indicates not yet calculated
        }
    }
    
}

int maximumPlanarSubset(int i, int j){
    //  cout << "running " << i << " " << j << endl;
    if (j <= i){ // 1
        return 0;
    }
    if (M[i][j-i] >= 0){ // 1
        return M[i][j-i];
    }
    if (chordList[i] == j){ 
        M[i][j-i] = 1 + maximumPlanarSubset(i+1, j-1);
        return M[i][j-i];
    }
    if (chordList[j] > i && chordList[j] < j ){
        // int k = chordList[j];
        int use = 1 + maximumPlanarSubset(i,chordList[j]-1) + maximumPlanarSubset(chordList[j]+1,j-1);
        int notUse = maximumPlanarSubset(i,j-1);
        if (use > notUse){
            M[i][j-i] = use;
            return M[i][j-i];
        }
        M[i][j-i] = notUse;
        return M[i][j-i];
    }
    M[i][j-i] = maximumPlanarSubset(i,j-1);
    return M[i][j-i];
}
int m(int i, int j){
    if (j <= i){
        return 0;
    }
    return M[i][j-i];
}
// int mstBottomUp(int endPoints){
//     for(int i = 0;i < endPoints-1; i++){
//         // cout << "i = " << i << endl;

//         if (chordList[i] == i+1){
//             // cout << "here" << endl;
//             M[i][1] = 1;
//             continue;
//         } 
//                     // cout << "there" << endl;

//         M[i][1] = 0;
//     }
//     for (int l = 2; l < endPoints; l++){
//         for (int i = 0; i < endPoints-l;i++){
//             int j = i+l;
//             // cout << "i = " << i << ", j = " << j << endl;
//             if (chordList[i] == j){
//                 M[i][l] = 1 + m(i+1,j-1);
//                 continue;
//             }
//             if (chordList[j] > i && chordList[j] < j ){
//                 int k = chordList[j];
//                 int use = 1 + m(i,k-1) + maximumPlanarSubset(chordList[j]+1,j-1);
//                 int notUse = m(i,j-1);
//                 if (use > notUse){
//                     M[i][l] = use;
//                     continue;
//                 }            
//                 M[i][l] = notUse;
//                 continue;
//                 // return M[i][j-i];
//             }
//             M[i][l] = m(i,j-1);
//         }
//     }
//     return M[0][endPoints-1];
// }
    
    // if (chordList[j] > i && chordList[j] < j ){
    //     // int k = chordList[j];
    //     int use = 1 + maximumPlanarSubset(i,chordList[j]-1) + maximumPlanarSubset(chordList[j]+1,j-1);
    //     int notUse = maximumPlanarSubset(i,j-1);
    //     if (use > notUse){
    //         M[i][j-i] = use;
    //         return M[i][j-i];
    //     }
    //     M[i][j-i] = notUse;
    //     return M[i][j-i];
    // }
    // M[i][j-i] = maximumPlanarSubset(i,j-1);
    // return M[i][j-i];



vector<int> result;
void output(fstream& fout, int i, int j,vector<int>& rst){
    if (j <= i){
        return;
    }
    if (chordList[i] == j){
        // fout << i << " " << j << endl;
        result.push_back(i);
        fout << i << " " << j << endl;
        output(fout, i+1, j-1,rst);
        return;
    }
    if (chordList[j] > i && chordList[j] < j ){
        if (m(i,j) == 1 + m(i,chordList[j]-1) + m(chordList[j]+1,j-1)){
            output(fout,i,chordList[j]-1,rst);
            // fout << chordList[j] << " " << j << endl;
            result.push_back(chordList[j]);
            output(fout,chordList[j]+1,j-1,rst);
            return;
        }
    }
    output(fout,i,j-1,rst);
}