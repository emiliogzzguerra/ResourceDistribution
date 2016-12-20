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

using namespace std;

int main() {
    ifstream archNum;
    
    
    
    vector<int> a{0, 1, 2, 3, 4};
    vector<int> b{5, 4, 2, 3, 1};
    
    int r1 = inner_product(a.begin(), a.end(), b.begin(), 0);
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

/*
 ifstream archNum;
 string iArrA[25], iArrB[25];
 int iSize = 0;
 string sInputA, sInputB;
 
 archNum.open("archivo.txt");
 
 while (archNum >> sInputA >> sInputB) {
 iArrA[iSize] = sInputA;
 iArrB[iSize] = sInputB;
 iSize++;
 }
 
 archNum.close();
 
 for (int i = 0; i<iSize; i++) {
 printf("%s %s\n",iArrA[i].c_str(),iArrB[i].c_str());
 }
 return 0;
*/
