// chainMatrixMult.cpp: Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

vector<int> getMultMin(int i, int j, int d[]){
	int p = i;
	int k = 0;
	if (i == j) {
		return{ 0, i };
	}
	else {
		int min = 99999;
		int count;
		int q = 0;
		for (p; p < j; p++) {
			count = getMultMin(i, p, d)[0] + getMultMin(p + 1, j, d)[0] + d[i - 1] * d[p] * d[j];
			if (count < min) {
				min = count;
				k = p;
			}
		}
		return{ min, k };
	}
}

int** generateMatrix1(int d) {
	int **arr = (int **)malloc(d * sizeof(int *));
	for (int i = 0; i < d; i++) {
		arr[i] = (int *)malloc(d * sizeof(int));
	}
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			arr[i][j] = -1;
		}
	}
	return arr;
}

int** generateMatrix2(int d) {
	int **arr = (int **)malloc(d * sizeof(int *));
	for (int i = 0; i < d; i++) {
		arr[i] = (int *)malloc(d * sizeof(int));
	}
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			arr[i][j] = 0;
		}
	}
	return arr;
}

template <size_t Q>
void splitString(string(&arr)[Q], string line)
{
	int i = 0;
	stringstream ssin(line);
	while (ssin.good() && i < Q){
		ssin >> arr[i];
		++i;
	}
}


void matMult(int n, int d[], int **M, int **P) {
	int k = 0;
	for (int i = 0; i < n; i++) {
		M[i][i] = 0;
	}
	for (int diag = 1; diag <= (n-1); diag++) {
		for (int i = 1; i <= (n - diag); i++) {
			int j = diag + i;
			vector<int> mins = getMultMin(i, j, d);
			M[i][j] = mins[0];
			P[i][j] = mins[1];
		}
	}
}

void order(int i, int j, int **P) {
	if (i == j) {
		cout << "M" << i;
	}
	else {
		int k = P[i][j];
		cout << "(";
		order(i, k, P);
		order(k + 1, j, P);
		cout << ")";
	}
}

void printMat1(int **C, int N) {
	for (int i = 0; i<N; i++) {
		cout << "" << endl;
		for (int j = 0; j<N; j++) {
			if (C[i][j] == -1 || (i==0 && j==0)) {
				cout << "   ";
			}
			else {
				cout << "" << C[i][j] << " ";
			}
		}
	}
	cout << "" << endl;
}
void printMat2(int **C, int N) {
	for (int i = 0; i<N; i++) {
		cout << "" << endl;
		for (int j = 0; j<N; j++) {
			if (C[i][j] == 0 || (i == 0 && j == 0)) {
				cout << "   ";
			}
			else {
				cout << "" << C[i][j] << " ";
			}
		}
	}
	cout << "" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n;
	string s;
	int d[100] = {};
	string arr[100] = {};
	cin.sync();
	cout << "Enter the total number of matricies :" << endl;
	cin >> n;
	cin.clear(); cin.sync();
	for (int i = 0; i < n-1; i++) {
		cout << "Enter the dimension for matrix " << i + 1 << ":" << endl;
		cin >> s;
		cin.clear(); cin.sync();
		splitString(arr, s);
		d[i] = atoi(arr[0].c_str());
		//only put the first number entered into d
	}
	cout << "Enter the dimension for matrix " << n << ":" << endl;
	getline(cin, s, '\n');
	cin.clear(); cin.sync();
	//std::size_t pos = s.find("10");
	//cout << "" << pos << ", " << s.substr(pos) << endl;
	splitString(arr, s);
	d[n-1] = atoi(arr[0].c_str());
	d[n] = atoi(arr[1].c_str());
	int **M = generateMatrix1(n+1);
	int **P = generateMatrix2(n+1);
	matMult(n, d, M, P);
	printMat1(M,n+1);
	printMat2(P,n+1);
	order(1, n, P);
	return 0;
}

