#include "Huffman.h"
using namespace std;

bool HuffmanCodeCompare(HuffmanNode* a,HuffmanNode* b){
	return a->freq != b->freq ? a->freq < b->freq: a->minAlphabet() < b->minAlphabet();
}

HuffmanNode* HuffmanCode(int symbol[],int freq[],int size){
	vector<HuffmanNode*> HufArray;
	for(int i = 0; i < size; ++i)
		HufArray.push_back(new HuffmanNode((char)symbol[i],freq[i],NULL,NULL));
	while(HufArray.size()!=1){
		HuffmanNode *Left = HufArray[0], *Right = HufArray[1];
		HufArray.erase(HufArray.begin());
		HufArray.erase(HufArray.begin());
		if(Left->minAlphabet() > Right->minAlphabet())
			swap(Left,Right);
		HufArray.push_back(new HuffmanNode('~',Left->freq+Right->freq,Left,Right));
		sort(HufArray.begin(),HufArray.begin()+HufArray.size(),HuffmanCodeCompare);
	}
	return HufArray[0];
}

vector< pair<char,string> > encode(HuffmanNode* root, string Code , int top){
	vector< pair<char,string> > temp1,temp2;
	if(root->left){
		Code += "0";
		temp1 = encode(root->left,Code,top+1);
		temp2.insert(temp2.end(),temp1.begin(),temp1.end());
		Code.erase(top);
	}
	if(root->right){
		Code += "1";
		temp1 = encode(root->right,Code,top+1);
		temp2.insert(temp2.end(),temp1.begin(),temp1.end());
		Code.erase(top);
	}
	if(!root->left && !root->right){
		pair<char,string> buf;
		buf.first = root->alphabet;
		buf.second = Code;
		temp2.push_back(buf);
	}
	return temp2;
}

char countChar(string in){
	char temp = 0;
	for(int i = 0; i < 8; ++i)
		temp += in[i] == i ? pow(2,7-i):0;
	return temp;
}

void HuffmanEncrypt(string inputfile,string outputfile){
	char buffer = '\0';
	int freq[256] = {}, size = 0;
	
	ifstream forTable(inputfile,ios::binary);
	for( ; ;++freq[(int)((unsigned char)buffer)], ++size){
		forTable.get(buffer);
		if(forTable.peek() == EOF)
			break;
	}
	forTable.close();
	
	int treeNodeNum = 0;
	for(int i = 0; i < 256; ++i)
		if(freq[i] != 0)
			++treeNodeNum;
	
	int freqTable[2][treeNodeNum];
	
	for(int i = 0, j =0; i < 256; ++i){
		if(freq[i]!=0){
			freqTable[0][j] = i;
			freqTable[1][j++] = freq[i];
		}
	}
	
	for(int i = 0; i < treeNodeNum - 1; ++i)
		for(int j = 0; j < treeNodeNum - 1 - i; ++j)
			if(freqTable[1][j] > freqTable[1][j+1]){
				swap(freqTable[1][j], freqTable[1][j+1]);
				swap(freqTable[0][j], freqTable[0][j+1]);
			}
	
	HuffmanNode* root = HuffmanCode(freqTable[0],freqTable[1],treeNodeNum);
	
	string Code;
	vector< pair<char,string> > HufCodeTable;
	HufCodeTable = encode(root,Code,0);
	
	string zeroOne;
	char buf2 = '\0';
	ifstream input(inputfile,ios::binary);
	ofstream output(outputfile,ios::binary);
	while(1){
		input.get(buf2);
		if(input.peek() == EOF)
			break;
		for(size_t i = 0; i < HufCodeTable.size(); ++i){
			if(HufCodeTable[i].first == buf2){
				zeroOne += HufCodeTable[i].second;
				break;
			}
		}
	}
	size_t outputfileSize = 24;
	outputfileSize += zeroOne.size();
	for(size_t i = 0; i < HufCodeTable.size(); ++i)
		outputfileSize += 2 + HufCodeTable[i].second.size();
	//output << "compression ratio:" << size * 100 / (int)outputfileSize << "%" << endl;
	output << HufCodeTable.size() << endl;
	for(size_t i = 0; i < HufCodeTable.size(); ++i)
		output << HufCodeTable[i].first << " " << HufCodeTable[i].second << endl;
	
	output << zeroOne;
	
	input.close();
	output.close();
}

void HuffmanDecrypt(string inputfile,string outputfile){
	char buf100[100],temp;
	int tableSize = 0;
	pair<char,string> buf;
	
	vector< pair<char,string> >HufmanTable;
	ifstream input(inputfile,ios::binary);
	ofstream output(outputfile,ios::binary);
	//input.getline(buf100,100);
	
	input >> tableSize;
	
	
	for(int i = 0; i < tableSize; ++i){
		input.get();
		input.get(buf.first);
		input.get();
		input >> buf.second;
		HufmanTable.push_back(buf);
	}
	
	input.get();
	
	string zeroOne;
	while(input.get(temp))
		zeroOne += temp;
	input.close();
	
	for(size_t start = 0; start < zeroOne.size(); )
		for(size_t i = 0; i < HufmanTable.size(); ++i)
			if(zeroOne.substr(start,HufmanTable[i].second.size()) == HufmanTable[i].second){
				output << HufmanTable[i].first;
				start += HufmanTable[i].second.size();
				break;
			}
	
	output.close();
}
