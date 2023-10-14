#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include <cmath>
#include <cstdlib>
#define Pi 3.14159265
using namespace std;
class Complex{
	private:
		double real;
		double ima;
	public:
		Complex():real(0), ima(0){};
		Complex(double r, double i):real(r), ima(i){};
		void setReal(double r){
			real=r;
		};
		void setIma(double i){
			ima=i;
		};
		double getReal(){
			return real;
		};
		double getIma(){
			return ima;
		};
		Complex operator *(const Complex& right){
			return Complex(real*right.real-ima*right.ima, ima*right.real+real*right.ima);
		};
		Complex operator +(const Complex& right){
			return Complex(real+right.real, ima+right.ima);
		};
};
void DFTencrypt(string inputfile, string outputfile);
void DFTdecrypt(string inputfile, string outputfile);
inline double removeError(double);
