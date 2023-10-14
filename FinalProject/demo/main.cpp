#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "DFT.h"
#include "Huffman.h"
using namespace std;
// ./main way e/d from to
int main(int argc, char* argv[]){
	string opt(argv[2]), inputfile(argv[3]), outputfile(argv[4]);
	if(strcmp(argv[1], "DFT") == 0)
		if(opt == "encrypt")
			DFTencrypt(inputfile,outputfile);
		if(opt == "decrypt")
			DFTdecrypt(inputfile,outputfile);
	else if(strcmp(argv[1], "Huffman") == 0)
		if(opt == "encrypt")
			HuffmanEncrypt(inputfile,outputfile);
		if(opt == "decrypt")
			HuffmanDecrypt(inputfile,outputfile);
	else if(strcmp(argv[1], "DCT") == 0){
		//string command = "python3 DCT.py "+opt+" "+inputfile+" "+outputfile;
		system("python3 DCT.py encrypt test.jpg");
	}
		
	return 0;
}
