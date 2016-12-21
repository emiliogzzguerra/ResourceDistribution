//
//  main.cpp
//  ResourceDistributionWithMatrixes
//
//  Created by Emilio Gonzalez on 12/20/16.
//  Copyright © 2016 Emilio Gonzalez. All rights reserved.
//

#include <iostream>
#include <functional>
#include <vector>
#include <fstream>
#include <map>
#include <numeric>


using namespace std;

void vectorSums(vector<vector<int>>vM, vector<int>&v,vector<int>&v2,int iSize){
    v = vector<int>(iSize);
    v2 = v;
    for(int i = 0; i<vM.size(); i++){
        for(int j = 0; j<vM[i].size(); j++){
            if(vM[j][i] == 1){
                v[i] += 1; //Meter info a sumatoria de conexiones
            }
            if(vM[i][j] == 1){
                v2[i] += 1;
            }
        }
    }
}

template<typename map_key, typename map_val>
void printMap(const map<map_key, map_val>& _map) {
    for(auto elem : _map){
        cout << elem.first << " " << elem.second << endl;
    }
}

void printVector(vector<int> vec){
    for(int i = 0; i<vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

void print2dVector(vector<vector<int>> vec){
    for(int i = 0; i<vec.size(); i++){
        for(int j = 0; j<vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
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
    
    //Initial values
    int iPlatino = 40;
    
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
    
    for(int i = 0; i<vAux2.size(); i++){ //Meter informacion de identificador numerico con letra y con score
        mScore.insert(make_pair(iKey, vAux2[i].second));
        mConnections.insert(make_pair(vAux2[i].first, iKey));
        iKey++;
    }
    
    vector<vector<int>> vM(vAux2.size(), vector<int>(vAux2.size())); //Crear matriz de conexiones vacias
    
    int iRow,iCol;
    
    vector<int> vMColAddition(vAux2.size()); //Crear matriz de sumatoria de columnas
    vector<int> vMRowAddition(vAux2.size()); //Crear matriz de sumatoria de filas

    
    for(auto i : vConnections){
        iRow = mConnections.find(i.second)->second;
        iCol = mConnections.find(i.first)->second;
        vM[iRow][iCol] = 1;
        //vMColAddition[iCol] += 1; //Meter info a sumatoria de conexiones
    }
    
    char cRank[4] = {'P','Z','E','D'};
    map<int,char> mRank; //Where the ranks will live
    
    vector<int> vEmpty(vAux2.size());
    bool bDeletedSomething;
    do{
        bDeletedSomething = false;
        vectorSums(vM, vMColAddition,vMRowAddition,vAux2.size());
        for(int i = 0; i<vMColAddition.size(); i++){
            if(vMColAddition[i] == 0){
                if(mScore.find(i)->second < iPlatino && vMRowAddition[i] != 0){
                    //cout << mScore.find(i)->second << " vs " << iPlatino << endl;
                    vM[i] = vEmpty;
                    bDeletedSomething = true;
                } else if (mScore.find(i)->second >= iPlatino){
                    if(mRank.find(i) == mRank.end()){
                        mRank.insert(make_pair(i, cRank[0]));
                        //cout << "Platino sin hijos!" << endl;
                    }
                }
            }
        }
    } while (bDeletedSomething);
    
    //printVector(vMColAddition);
    
    //cout << endl;
    //print2dVector(vM);
    
    int iJumper = 20;
    
    for(int i = 0; i<vMColAddition.size(); i++){
        if(vMColAddition[i] != 0){
            switch (vMColAddition[i]) {
                case 1:
                    if(mScore.find(i)->second >= iJumper){
                        mRank.insert(make_pair(i, cRank[0]));
                        //cout << "Platino con hijos!" << endl;
                    } else {
                        //Borrar 1 existente y tomar en cuenta su posicion
                        int iPos;
                        
                        for(int j = 0; j<vM.size(); j++){
                            if(vM[j][i] == 1){
                                iPos = j;
                                vM[j][i] = 0;
                            }
                        }
                        int iPadre;
                        for(int k = 0; k<vM[i].size(); k++){
                            if(vM[i][k] == 1){
                                iPadre = k;
                                break;
                            }
                        }
                        //Borro i y pongo hijo de el borrado (ipos)
                        for(int l = 0; l<vM.size(); l++){
                            if(l == i){
                                vM[l][iPadre] = 0;
                            } else if (l == iPos){
                                vM[l][iPadre] = 1;
                            }
                        }
                    }
                    break;
                case 2:
                    if(mScore.find(i)->second < iJumper){
                        mRank.insert(make_pair(i, cRank[0]));
                    } else if (mScore.find(i)->second >= iJumper){
                        mRank.insert(make_pair(i, cRank[1]));
                    }
                    //cout << "Zafiro!" << endl;
                    break;
                default:
                    mRank.insert(make_pair(i, cRank[2]));
                    //cout << "Esmeralda!" << endl;
                    break;
            }
        }
    }
    
    /********************* ASIGNACION DE PUNTOS ***************************/
    
    map<int,int> mFinalScore; //Aquí estará la relacion entre personas y puntos finales
    int iArrScore[3] = {60, 80, 100};
    int iMultiplicadores[3] = {2,2,2}; //Multiplicadores de cada nivel
    
    print2dVector(vM);
    
    pair<int,int> pPos;
    vector<vector<int>> vMAux(vAux2.size());//Crear matriz de conexiones vacia
    
    for(int i = 0; i<vAux2.size(); i++){
        if(mRank.find(i) == mRank.end()){
            mFinalScore.insert(make_pair(i, 0));
        } else {
            switch (mRank.find(i)->second) {
                case 'P':
                    iScore = vMColAddition[i] * iArrScore[0]; //Cantidad de hijos * puntos que suben
                    iScore += iMultiplicadores[0] * mScore.find(i)->second; //Mis puntos * multiplicador
                    mFinalScore.insert(make_pair(i, iScore));
                    break;
                case 'Z':
                    iScore = vMColAddition[i] * iArrScore[1];
                    iScore += iMultiplicadores[1] * mScore.find(i)->second;
                    mFinalScore.insert(make_pair(i, iScore));
                    break;
                    
                case 'E':
                    
                    vMAux = vM;
                    for(int a = 0; a<vMColAddition[i]; a++){
                        vMAux[a][i] = 0;
                    }
                    print2dVector(vMAux);
                    for(int j = 0; j<vMColAddition[i]; j++){
                        for(int k = 0; k<vM[i].size(); k++){
                            if(vM[k][i] == 1){
                                pPos = make_pair(i, j);
                                break;
                            }
                        }
                        
                    }         
                    iScore = vMColAddition[i] * iArrScore[1];
                    iScore += iMultiplicadores[1] * mScore.find(i)->second;
                    mFinalScore.insert(make_pair(i, iScore));
                    
                    break;
                    
                default:
                    cout << "Fuck" << endl;
                    break;
            }
            int iMaterial = mRank.find(i)->second;
            
        }
    }
    
    
    
    return 0;
}

/*
 
 vector<int> a{0, 1, 2, 3, 4};
 vector<int> b{5, 4, 2, 3, 1};
 
 int r1 = inner_product(a.begin(), a.end(), b.begin(), 0);
  insert code here...
 cout << "Hello, World!\n";

 
*/
