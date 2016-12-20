//
//  main.cpp
//  ResourceDistributionWithMatrixes
//
//  Created by Emilio Gonzalez on 12/20/16.
//  Copyright © 2016 Emilio Gonzalez. All rights reserved.
//

#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
#include <fstream>
#include <map>


using namespace std;

void print2dVector(vector<vector<int>> vec){
    for(int i = 0; i<vec.size(); i++){
        for(int j = 0; j<vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

bool pairCompare(const pair<int, int> &firstElem, const pair<int,int> &secondElem) {
    return firstElem.first < secondElem.first;
}

bool pairCompareSecond(const pair<int, int> &firstElem, const pair<int,int> &secondElem) {
    if(firstElem.first == secondElem.first){
        return firstElem.second < secondElem.second;
    }
    return false;
}

int main() {
    map<char,int> mConnections;
    map<int,int> mScore;
    
    ifstream doc;
    
    doc.open("connections.txt");
    
    char a, comma, b;
    
    vector<pair<char,char>> vConnections;
    
    while(doc >> a >> comma >> b){
        vConnections.push_back(make_pair(a, b));
    }

    sort(vConnections.begin(), vConnections.end(), pairCompare);
    
    sort(vConnections.begin(), vConnections.end(), pairCompareSecond);

    doc.close();

    doc.open("score.txt");
    
    char cKey;
    int iScore;
    
    vector <pair<char,int>> vAux2;
    
    while(doc >> cKey >> comma >> iScore){ //Meter scores en vector de pares
        vAux2.push_back(make_pair(cKey, iScore));
    }
    
    sort(vAux2.begin(), vAux2.end(), pairCompare); //Sortear scores por sus padres
    
    doc.close();
    
    int iKey = 0;
    
    for(int i = 0; i<vAux2.size(); i++){
        mScore.insert(make_pair(iKey, vAux2[i].second));
        mConnections.insert(make_pair(vAux2[i].first, iKey));
        iKey++;
    }
    
    vector<vector<int>> vM(vAux2.size(), vector<int>(vAux2.size()));
    
    print2dVector(vM);
    
    cout << endl;
    
    int iRow,iCol;
    
    for(auto i : vConnections){
        iRow = mConnections.find(i.second)->second;
        iCol = mConnections.find(i.first)->second;
        vM[iRow][iCol] = 1;
    }
    
    print2dVector(vM);
    
    cout << endl;
    
    
    
    
    //vector<int> a{0, 1, 2, 3, 4};
    //vector<int> b{5, 4, 2, 3, 1};
    
    //int r1 = inner_product(a.begin(), a.end(), b.begin(), 0);
    // insert code here...
    //cout << "Hello, World!\n";
    return 0;
}

/*
int iCount = 0;

for(int i = 0; i<vAux.size(); i++){
    if(mConnections.find(vAux[i].first) == mConnections.end()){
        mConnections.insert(make_pair(vAux[i].first,iCount));
        mScore.insert(make_pair(iCount,0));
        iCount++;
    }
}


    
*/
