#ifndef SYMBOLCODE_H
#define SYMBOLCODE_H

#include <fstream>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
 * Define SymbolCode Class
 */
class SymbolCode {
private:
    char symbol;
    int frequency;
    string code;
public:
    SymbolCode( char in_symbol, int in_frequency );
    char getSymbol( void );
    int getFrequency( void );
    string getCode( void );
    void addCode( string in_code );
    void printSymbolCode(void);
    void setFrequency( int freq );
};

SymbolCode::SymbolCode( char in_symbol, int in_frequency ) {
    symbol = in_symbol;
    frequency = in_frequency;
    code = "";
}

char SymbolCode::getSymbol( void ) {
    return symbol;
}

int SymbolCode::getFrequency( void ) {
    return frequency;
}

string SymbolCode::getCode( void ) {
    return code;
}

void SymbolCode::addCode( string in_code ) {
    code += in_code;
}

void SymbolCode::printSymbolCode( void ) {
    cout << "Symbol: " << symbol;
    cout << " Freq: " << frequency;
    cout << " Code: " << code << endl;
}

void SymbolCode::setFrequency( int freq ) {
    frequency = freq;
}

#endif
/*
 * End SymbolCode Class
 */

