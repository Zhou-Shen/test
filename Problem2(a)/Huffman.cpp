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
#define OUTPUT_FILE "../OutputData/hf_text.dat"


using namespace std;

// store the symbol sorted by frequency of which frequency not zero
vector<SymbolCode> symbol;

// store the input frequency
int frequency[ MAX_CHAR ];

// store the mapping from symbol to code
map<char, string> symbolToCode;

struct TreeNode {
    TreeNode * left;
    TreeNode * right;
    char symbol;
};

void dfs(TreeNode * root, string code, map<char, string>& symbolToCode){
    if(root == NULL){
        return;
    }
    if(root->left == NULL && root->right == NULL){
        symbolToCode[root->symbol] = code;
        return;
    }
    if(root->left != NULL){
        dfs(root->left, code + '0', symbolToCode);
    }
    if(root->right != NULL){
        dfs(root->right, code + '1', symbolToCode);
    }
}

void buildMap(map<char, string> & symbolToCode){
    TreeNode* rootNode = new TreeNode;

    map<char, TreeNode*> symbolToNode;
    while(true){
        TreeNode* root = new TreeNode;
        
        
        double minFreq = INT_MAX;
        char minSymbol;
        int minIndex = -1;
        for(int i = 0; i < symbol.size(); i++){
            if(symbol[i].getFrequency() < minFreq && symbol[i].getFrequency() > 0){
                minFreq = symbol[i].getFrequency();
                minSymbol = symbol[i].getSymbol();
                minIndex = i;
            }
        }
        TreeNode* minNode = new TreeNode;
        if(symbolToNode[minSymbol] != NULL){
            minNode = symbolToNode[minSymbol];
        } else {
            minNode->symbol = minSymbol;
            minNode->left = NULL;
            minNode->right = NULL;
        }
        root->left = minNode;
        root->symbol = minNode->symbol;

        double minFreq2 = INT_MAX;
        char minSymbol2;
        int minIndex2 = -1;
        for(int i = 0; i < symbol.size(); i++){
            if(symbol[i].getFrequency() < minFreq2 && symbol[i].getFrequency() > 0 && i != minIndex){
                minFreq2 = symbol[i].getFrequency();
                minSymbol2 = symbol[i].getSymbol();
                minIndex2 = i;
            }
        }
        if(minIndex2 == -1){
            rootNode = symbolToNode[minSymbol];
            break;
        }
        TreeNode* minNode2 = new TreeNode;
        if(symbolToNode[minSymbol2] != NULL){
            minNode2 = symbolToNode[minSymbol2];
        } else {
            minNode2->symbol = minSymbol2;
            minNode2->left = NULL;
            minNode2->right = NULL;
        }

        
        root->right = minNode2;

        symbol[minIndex].setFrequency(symbol[minIndex].getFrequency() + symbol[minIndex2].getFrequency());
        symbol[minIndex2].setFrequency(0);
        symbolToNode[minSymbol] = root;
        symbolToNode[minSymbol2] = NULL;

    }

    dfs(rootNode, "", symbolToCode);
}

int main (int argc, char* argv[]) {

    // Read the input file, calculate frequency of each symbol and sort
    InputAndSort(INPUT_FILE, symbol, frequency);
    
    // Calculate the entropy
    CalculateEntropy(symbol);

    // Build the mapping from symbol to code
    buildMap(symbolToCode);

    // Encode and output the input file according to the mapping
    OutputEncodeData(INPUT_FILE, OUTPUT_FILE, symbolToCode);

    return 0;
}
