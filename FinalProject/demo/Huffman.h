#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

class HuffmanNode{
	public:
		char alphabet;
		int freq;
		HuffmanNode *left, *right;
		HuffmanNode(char a,int f,HuffmanNode* l,HuffmanNode* r):alphabet(a),freq(f),left(l),right(r){};
		int minAlphabet(){
			int smellest = (int)alphabet;
			if(left!=NULL && left->minAlphabet() < smellest)
				smellest = left->minAlphabet();
			if(right!=NULL && right->minAlphabet() < smellest)
				smellest = right -> minAlphabet();
			return smellest;
		};
};

bool HuffmanCodeCompare(HuffmanNode*,HuffmanNode*);
HuffmanNode* HuffmanCode(int [],int [],int);
vector< pair<char,string> > encode(HuffmanNode*, string, int);
void HuffmanEncrypt(string inputfile,string outputfile);
void HuffmanDecrypt(string inputfile,string outputfile);
