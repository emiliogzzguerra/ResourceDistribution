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
#include <queue>



using namespace std;

vector<vector<int>> multiplyMatrix(vector<vector<int>> v1,vector<vector<int>> v2, int n){
    vector<vector<int>> vRes(n,vector<int>(n));
    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            for(int k = 0; k < n; ++k)
            {
                vRes[i][j] += v1[i][k] * v2[k][j];
            }
    return vRes;
}

int vectorColSum(vector<vector<int>>vM,int iPos){
    int iRes = 0;
    for(int j = 0; j<vM[iPos].size(); j++){
        if(vM[j][iPos] == 1){
            iRes += 1; //Meter info a sumatoria de conexiones
        }
    }
    return iRes;
}

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

template<typename v_key, typename v_val>
void printPairVector(const vector<v_key, v_val>& output){
    for(int i = 0; i < output.size(); i++)
    {
        cout << output[i].first << "," << output[i].second << endl;
    }
}

void printVector(vector<int> vec){
    for(int i = 0; i<vec.size(); i++){
        cout << vec[i] << " ";
    }
    cout << endl;
}

void print2dVector(vector<vector<int>> vec){
    for(int a = 0; a<vec.size(); a++){
        cout << a << " ";
    }
    for(int i = 0; i<vec.size(); i++){
        cout << i << " ";
        for(int j = 0; j<vec[i].size(); j++){
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
/*
bool pairCompare(const pair<int, int> &firstElem, const pair<int,int> &secondElem) {
    return firstElem.first < secondElem.first;
}

bool pairCompareSecond(const pair<int, int> &firstElem, const pair<int,int> &secondElem) {
    if(firstElem.first == secondElem.first){
        return firstElem.second < secondElem.second;
    }
    return false;
}
*/

int main() {
    
    //Initial values
    int iPlatino = 40;
    
    map<char,int> mConnections;
    map<int,int> mScore;
    
    ifstream doc;
    
    //Obtener conexiones
    doc.open("connect.txt");
    
    int a, b;
    char comma;
    
    vector<pair<int,int>> vConnections;
    
    while(doc >> a >> comma >> b){
        vConnections.push_back(make_pair(a, b));
    }
    
//    cout<< "--------------Inicial--------------" << endl;
//    printPairVector(vConnections);

    sort(vConnections.begin(), vConnections.end());
//    cout<< "--------------PrimerSort--------------" << endl;
//    printPairVector(vConnections);
    
    doc.close();
    
    //printPairVector(vConnections);
    
    //Obtener puntos de cada nodo
    doc.open("sc.txt");
    
    int cKey;
    int iScore;
    
    vector <pair<int,int>> vAux2;
    
    while(doc >> cKey >> comma >> iScore){ //Meter scores en vector de pares
        vAux2.push_back(make_pair(cKey, iScore));
    }
    
    //cout<< "--------------Inicial--------------" << endl;
    //printPairVector(vAux2);
    
    sort(vAux2.begin(), vAux2.end()); //Sortear scores por sus padres
    
    //cout<< "--------------PrimerSort--------------" << endl;
    //printPairVector(vAux2);
    
    doc.close();

    
    //Meter info que obtuvimos a sus respectivos mapas
    
    int n = vAux2.size();
    
    int iKey = 0;
    
    for(int i = 0; i<n; i++){ //Meter informacion de identificador numerico con letra y con score
        mScore.insert(make_pair(iKey, vAux2[i].second));
        mConnections.insert(make_pair(vAux2[i].first, iKey));
        iKey++;
    }
    
    
    
    vector<vector<int>> vM(n, vector<int>(n)); //Crear matriz de conexiones vacias
    
    int iRow,iCol;
    
    vector<int> vMColAddition(n); //Crear matriz de sumatoria de columnas
    vector<int> vMRowAddition(n); //Crear matriz de sumatoria de filas

    
    for(auto i : vConnections){
        iRow = mConnections.find(i.second)->second;
        iCol = mConnections.find(i.first)->second;
        vM[iRow][iCol] = 1;
        //vMColAddition[iCol] += 1; //Meter info a sumatoria de conexiones
    }
    
    //print2dVector(vM);
    
    char cRank[4] = {'P','Z','E','D'};
    map<int,char> mRank; //Where the ranks will live
    
    vector<int> vEmpty(n);
    bool bDeletedSomething;
    do{
        bDeletedSomething = false;
        vectorSums(vM, vMColAddition,vMRowAddition,n);
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
    
    for(int j = 0; j<vMColAddition.size(); j++){
        if(vMColAddition[j] != 0){
            switch (vMColAddition[j]) {
                case 1:
                    if(mScore.find(j)->second >= iJumper){
                        mRank.insert(make_pair(j, cRank[0]));
                        //cout << "Platino con hijos!" << endl;
                    } else {
                        //Borrar 1 existente y tomar en cuenta su posicion
                        int iPos;
                        
                        for(int i = 0; i<vM.size(); i++){
                            if(vM[i][j] == 1){
                                iPos = i;
                                vM[i][j] = 0;
                            }
                        }
                        int iPadre;
                        for(int k = 0; k<vM[j].size(); k++){
                            if(vM[j][k] == 1){
                                iPadre = k;
                                break;
                            }
                        }
                        //Borro i y pongo hijo de el borrado (ipos)
                        for(int l = 0; l<vM.size(); l++){
                            if(l == j){
                                vM[l][iPadre] = 0;
                            } else if (l == iPos){
                                vM[l][iPadre] = 1;
                            }
                        }
                    }
                    break;
                case 2:
                    if(mScore.find(j)->second < iJumper){
                        mRank.insert(make_pair(j, cRank[0]));
                    } else if (mScore.find(j)->second >= iJumper){
                        mRank.insert(make_pair(j, cRank[1]));
                    }
                    //cout << "Zafiro!" << endl;
                    break;
                default:
                    mRank.insert(make_pair(j, cRank[2]));
                    //cout << "Esmeralda!" << endl;
                    break;
            }
        }
    }
    
    // ASIGNACION DE puntos
    
    map<int,int> mFinalScore; //Aquí estará la relacion entre personas y puntos finales
    int iArrScore[3] = {60, 80, 100};
    int iMultiplicadores[3] = {2,2,2}; //Multiplicadores de cada nivel
    int iPuntosProfundidad = 20;
    int iPuntosEsmeralda = 300;
    int iColumnSum;
    int iTemporal = 0;
    
    pair<int,int> pPos = make_pair(-1, 0);
    vector<vector<int>> vMatrizOriginal(n,vector<int>(n));
    vector<vector<int>> vMatrizAuxiliar(n,vector<int>(n));
    vector<int> vColSums;
    int iCountDepth = 0;
    bool bBreak = true;
    int iScoreLastChance = 0;
    vector<int> vPosicionesUnos;
    vector<int> vPosicionesUnosAux(n);
    int iCountHijos = 0;
    
    printMap(mRank);
    
    for(int i = 0; i<n; i++){
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
                    iScore = 0;
                    cout << "Esmeralda" << endl;
                    vMatrizOriginal = vM;
                    vMatrizAuxiliar = vMatrizOriginal;
                    print2dVector(vMatrizOriginal);
                    
                    cout << "Antes de todo Original:" << endl;
                     print2dVector(vMatrizOriginal);
                    
                    for(int a = 0; a<vMatrizAuxiliar.size(); a++){
                        if(vMatrizAuxiliar[a][i] == 1){
                            vPosicionesUnos.push_back(a);
                            cout << a << endl;
                        }
                        vMatrizAuxiliar[a][i] = 0;
                    }
                    
                    cout << "Auxiliar con columna vacia: (" << i << ")" << endl;
                    print2dVector(vMatrizAuxiliar);
                
                    for(auto k : vPosicionesUnos){
                        
                        vMatrizAuxiliar[k][i] = 1;
                        
                        cout << "Auxiliar en " << iCountDepth << ":  (" << i << ")"<< endl;
                         print2dVector(vMatrizAuxiliar);
                        
                        while(iCountDepth<6 && bBreak){
                            iTemporal = 0;
                            for(int m = 0; m<n; m++){
                                 cout << "m = " << m << endl;
                                 cout << "i = " << i << endl;
                                 cout << "Sumatoria de columna = " << vectorColSum(vMatrizAuxiliar, i) << endl;
                                 cout << endl;
                                if(vMatrizAuxiliar[vPosicionesUnosAux[i]][i] == 1 && mRank.find(vPosicionesUnosAux[i])->second == 'E'){
                                    
                                     cout << "En auxiliar se encontró : " << vMatrizAuxiliar[vPosicionesUnosAux[i]][i] << endl;
                                     cout << "En la matriz de rank se encontró: " << mRank.find(vPosicionesUnosAux[i])->second << endl;
                                    
                                    iTemporal = iCountDepth * iPuntosProfundidad;
                                    iTemporal += iPuntosEsmeralda;
                                    
                                    bBreak = false;
                                    break;
                                    
                                } else if (vectorColSum(vMatrizAuxiliar, i) == 0) {
                                     cout << m << " - Elseif" << endl << endl;
                                    iTemporal = (iCountDepth-1) * iPuntosProfundidad;
                                    iTemporal += iArrScore[2]; // +100
                                    bBreak = false;
                                    break;
                                
                                } else {
                                    if(vMatrizAuxiliar[vPosicionesUnosAux[i]][i] == 1){
                                        cout << "Primer condicion correcta" << endl;
                                    } else {
                                        cout << "Primer condicion INCORRECTA" << endl;
                                    }
                                    
                                    cout << vPosicionesUnosAux[i] << endl;
                                    
                                    cout << mRank.find(vPosicionesUnosAux[i])->second << endl;
                                    
                                    cout << m << " - Else" << endl << endl;
                                    
                                    iCountDepth++;
                                    
                                    cout << "iCountDepth = " << iCountDepth << endl;
                                    
                                    if(iCountDepth >= 5){
                                        iTemporal = iCountDepth * iPuntosProfundidad;
                                        iTemporal += iArrScore[2]; // +100
                                        bBreak = false;
                                        break;
                                    } else {
                                        vMatrizAuxiliar = multiplyMatrix(vMatrizOriginal, vMatrizAuxiliar, n);
                                        
                                         cout << "Auxiliar*Original en " << iCountDepth << ": " << endl;
                                         print2dVector(vMatrizAuxiliar);
                                        
                                         cout << "---------------------------" << endl;
                                        while (!vPosicionesUnosAux.empty())
                                        {
                                            vPosicionesUnosAux.pop_back();
                                        }
                                        for(int a = 0; a<vMatrizAuxiliar.size(); a++){
                                            if(vMatrizAuxiliar[a][i] == 1){
                                                vPosicionesUnosAux.push_back(a);
                                                cout << "HERE" <<  a << endl;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << "Puntos que el hijo " << iCountHijos << " contribuyo: " << iTemporal << endl;
                        iScore += iTemporal;
                        cout << "iScore en " << iCountHijos << " hijo: " << iScore << endl;
                        iCountHijos ++;

                         cout << "Salimos del while" << endl;
                        bBreak = true;
						iCountDepth = 0;
                        
                        vMatrizAuxiliar = vMatrizOriginal;
                        for(int a = 0; a<vMatrizAuxiliar.size(); a++){
                            vMatrizAuxiliar[a][i] = 0;
                        }
                    }
                    iCountHijos = 0;
                    iScore += iMultiplicadores[2] * mScore.find(i)->second;
                    mFinalScore.insert(make_pair(i,iScore));
                    iTemporal = 0;
                    while (!vPosicionesUnos.empty())
                    {
                        vPosicionesUnos.pop_back();
                    }
                    break;
                    
                default:
                    // cout << "Esto no debería pasar :/ hahah" << endl;
                    break;
            }            
        }
    }
    printMap(mFinalScore);

    return 0;
}
