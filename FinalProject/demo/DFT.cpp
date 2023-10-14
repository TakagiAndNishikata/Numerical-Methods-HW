#include "DFT.h"
using namespace std;
void DFTencrypt(string inputfile, string outputfile){
	ifstream fin(inputfile);
	ofstream fout(outputfile);
	for(string line; getline(fin, line); fout << endl){   //read the input file line by line
		const int L=line.length();
		Complex F[L][L], encrIn[L], encrOut[L];
		for(int i=0; i<L; i++)		//s=[s0, s1, s2,...s(L-1)]
			encrIn[i]=Complex((double)line[i], 0.0);
		for(int k=0; k<L; k++){     //create L*L Fourier Matrix
			for(int n=0; n<L; n++){
				F[k][n].setReal(removeError(cos(-k*n*2*Pi/L)));
				F[k][n].setIma(removeError(sin(-k*n*2*Pi/L)));
			}
		}
		for(int i=0; i<L; i++){    //S=F*s
			for(int j=0; j<L; j++)
				encrOut[i]=encrOut[i]+F[i][j]*encrIn[j];
			encrOut[i].setReal(removeError(encrOut[i].getReal()));
			encrOut[i].setIma(removeError(encrOut[i].getIma()));
			fout << encrOut[i].getReal() << " ";
			if(i!=0)
				fout << encrOut[i].getIma() << " ";
		}
	}
	fin.close();
	fout.close();
}
void DFTdecrypt(string inputfile, string outputfile){
	ifstream fin(inputfile);
	ofstream fout(outputfile);
	int test = 0;
	for(string line; getline(fin, line); fout << endl ){     //read the input file line by line
		cout << line << test++ << endl;
		if(line == "")
			break;
		stringstream ss;
		vector<Complex> decrIn;
		ss << line;

		double buffer1,buffer2;
		if(ss >> buffer1){
			decrIn.push_back(Complex(buffer1,0));   //the first ima zero is omitted
		}
		for(; ss >> buffer1 >> buffer2 ; decrIn.push_back(Complex(buffer1,buffer2)));   //S=[S0, S1, S2,...S(L-1)]
		const int L=decrIn.size();
		Complex IF[L][L], decrOut[L];
		for(int k=0; k<L; k++){     //create L*L Inverse Fourier Matrix
			for(int n=0; n<L; n++){
				IF[k][n].setReal(removeError(cos(k*n*2*Pi/L)/L));
				IF[k][n].setIma(removeError(sin(k*n*2*Pi/L)/L));
			}
		}
		for(int i=0; i<L; i++){     //s=IF*S
			for(int j=0; j<L; j++){
				decrOut[i]=decrOut[i]+IF[i][j]*decrIn[j];
			}
			decrOut[i].setReal(round(decrOut[i].getReal()));
			decrOut[i].setIma(round(decrOut[i].getIma()));
			fout << (char)decrOut[i].getReal();
		}
		cout << "end" << endl;
    }
	fin.close();
	fout.close();
}
inline double removeError(double data){     //remove trigonometric rounding errors
    return ((abs(data*1000000)<1)? 0.0:data);
}
