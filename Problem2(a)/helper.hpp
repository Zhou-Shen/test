/************************** Start of helper.h *************************/

#ifndef HELPER_H
#define HELPER_H

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include "SymbolCode.hpp"

#define MAX_CHAR 256


using namespace std;

int binaryToInt(string s, int num){
    int n = 0;
    for(int i = 0; i < num; i++){
        n += (s[i]-'0') * pow(2,num - 1 - i);
    }  
    return n;
}

void OutputEncodeData(string INPUT_FILE, string OUTPUT_FILE, map<char, string> symbolToCode){

    ifstream inputFile(INPUT_FILE, ifstream::binary);
    vector<char> vectorfile((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
    ofstream outputFile(OUTPUT_FILE);
    string encodeResult;
    for(int i = 0; i < vectorfile.size(); i++){
        encodeResult += symbolToCode[vectorfile[i]];
        while(encodeResult.length() > 8){
            outputFile << (char)binaryToInt(encodeResult, 8);
            encodeResult = encodeResult.substr(8);
        }
    }
    if(encodeResult.length()>0){
        outputFile << (char)binaryToInt(encodeResult, encodeResult.length());
    }
    outputFile.close();
}

void InputAndSort(const char * INPUT_FILE, vector<SymbolCode> & symbol, int * frequency ){
    FILE * pFile;
    int c;
    int n = 0;

    pFile = fopen(INPUT_FILE,"rb");
    if (pFile==NULL) {
        perror ("Error opening file");
    } else {
        int i;
        for ( i=0; i<MAX_CHAR; i++ ) {
            frequency[ i ] = 0;
        }
        do {
            c = fgetc (pFile);
            if ( c != EOF ) {
                frequency[ c ] ++;

                // printf( "%c", c );
            }
        } while (c != EOF);
        fclose (pFile);
    }
    
    // print the frequency information
    cout << endl << endl;
    int i;
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            printf( "%d, %c: %d\n", i, i, frequency[ i ] );
        }
    }
    // insert and sort the symbol
    printf( "\n\n" );
    for ( i=0; i<MAX_CHAR; i++ ) {
        if ( frequency[ i ] != 0 ) {
            if ( symbol.empty() ) {
                SymbolCode newSymbol( i, frequency[ i ] );
                symbol.push_back( newSymbol );
            } else {
                int j;
                vector<SymbolCode>::iterator it;
                it = symbol.begin();
                for ( j=0; j<symbol.size(); j++ ) {
                    if ( frequency[ i ] >= symbol[ j ].getFrequency() ) {
                        SymbolCode newSymbol( i, frequency[ i ] );
                        symbol.insert( it, newSymbol );
                        break;
                    } else if ( j == symbol.size() - 1 ) {
                        SymbolCode newSymbol( i, frequency[ i ] );
                        symbol.push_back( newSymbol );
                        break;
                    }
                    it ++;
                }
            }
        }
    }
}

void CalculateEntropy(vector<SymbolCode> symbol){
    double sumFreq;
    double entropy;
    for(int i = 0; i < symbol.size(); i++){
        SymbolCode symb = symbol[i];
        sumFreq += symb.getFrequency();
    }
    for(int i = 0; i < symbol.size(); i++){
        SymbolCode symb = symbol[i];
        entropy -= log2(symb.getFrequency() / sumFreq)* (symb.getFrequency() / sumFreq);
    }
    
    cout << "Entropy is " << entropy << endl;
    cout << "Number of symbol is " << sumFreq << endl;
}
#endif
/*************************** End of helper.h **************************/