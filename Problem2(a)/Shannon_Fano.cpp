#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <math.h>
#include "helper.hpp"
#include "SymbolCode.hpp"

#define MAX_CHAR 256
#define INPUT_FILE "../InputData/text.dat"
#define OUTPUT_FILE "../OutputData/sn_text.dat"

using namespace std;


// store the symbol sorted by frequency of which frequency not zero
vector<SymbolCode> symbol;

// store the input frequency
int frequency[ MAX_CHAR ];

// store the mapping from symbol to code
map<char, string> symbolToCode;

void shannonFano( int in_begin, int in_end ) {
    // not a valid parameters input
    if ( in_begin >= in_end ) {
        return;
    }
    
    // only 2 symbol left
    if ( in_begin == in_end - 1 ) {
        symbol.at( in_begin ).addCode( "0" );
        symbol.at( in_end ).addCode( "1" );
        return;
    }
    
    int highPtr = in_begin; // highPtr will go downward
    int lowPtr = in_end;
    int highSum = symbol.at( highPtr ).getFrequency();
    int lowSum = symbol.at( lowPtr ).getFrequency();
    
    // move the highPtr down and lowPtr up until highSum and lowSum close
    while ( highPtr != lowPtr - 1 ) {
        if ( highSum > lowSum ) {
            lowPtr --;
            lowSum += symbol.at( lowPtr ).getFrequency();
        } else {
            highPtr ++;
            highSum += symbol.at( highPtr ).getFrequency();
        }
    }
    
    int i;
    for ( i=in_begin; i<=highPtr; i++ ) {
        symbol.at( i ).addCode( "0" );
    }
    for ( i=lowPtr; i<=in_end; i++ ) {
        symbol.at( i ).addCode( "1" );
    }
    
    shannonFano( in_begin, highPtr );
    shannonFano( lowPtr, in_end );
}

void buildMap(map<char, string> & symbolToCode){
    for(int i = 0; i < symbol.size(); i++){
        SymbolCode symb = symbol[i];
        symbolToCode[symb.getSymbol()] = symb.getCode();
    }
}

int main (int argc, char* argv[]) {
    
    // Read the input file, calculate frequency of each symbol and sort
    InputAndSort(INPUT_FILE, symbol, frequency);
    
    // Apply Shannon
    shannonFano( 0, symbol.size() - 1 );

    // Calculate the entropy
    CalculateEntropy(symbol);

    // Build the mapping from symbol to code
    buildMap(symbolToCode);

    // Encode and output the input file according to the mapping
    OutputEncodeData(INPUT_FILE, OUTPUT_FILE, symbolToCode);
    
    return 0;
}
