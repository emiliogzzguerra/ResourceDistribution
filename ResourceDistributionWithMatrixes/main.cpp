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

int main() {
    map<char,int> mConnections;
    map<int,int> mScore;
    
    ifstream doc;
    
    doc.open("connections.txt");
    
    char a, comma, b;
    
    int i = 0;
    
    while(doc >> a >> comma >> b){
        if(mConnections.find(a) == mConnections.end()){
            mConnections.insert(make_pair(a,i));
            mScore.insert(make_pair(i,0));
            i++;
        }
    }
    
    doc.close();

    doc.open("score.txt");
    
    int iKey,iScore;
    
    while(doc >> iKey >> comma >> iScore){
        mScore.find(iKey)->second = iScore;
    }
    
    doc.close();
    
    
    
    //vector<int> a{0, 1, 2, 3, 4};
    //vector<int> b{5, 4, 2, 3, 1};
    
    //int r1 = inner_product(a.begin(), a.end(), b.begin(), 0);
    // insert code here...
    //cout << "Hello, World!\n";
    return 0;
}

/*
 ifstream archNum;
 string iArrA[25], iArrB[25];
 int iSize = 0;
 string sInputA, sInputB;
 mConexiones archNum.open("archivo.txt");
 
 while (archNum >> sInputA >> sInputB) {
 iArrA[iSize] = sInputA;
 iArrB[iSize] = sInputB;
 iSize++;
 }
 mConexiones archNum.close();
 
 for (int i = 0; i<iSize; i++) {
 printf("%s %s\n",iArrA[i].c_str(),iArrB[i].c_str());
 }
 return 0;
*/
