#pragma once
#include <iostream>
#include <string>
#include "HashTable.h"
#include <fstream>
#define seed 12345678
#define M 10000
#define notFound -999
using namespace std;
int i = 4, d = 2, f = 2;
struct datas {
	int probe;
	double load;
	//datas() : probe(0), load(0) {};
	datas() {};
	datas(int probe, double load) :probe(probe), load(load) {};
};

datas* fail_Ins = new datas[M + 1]; //THERE WAS A BUFFER OVERFLOW IN FAIL_INS

void changeRatios(int &i, int &d, int &f) {
	if (rand() % 3 == 0) {
		i = 6, d = 1, f = 1;
	}
	else if (rand() % 3 == 1) {
		i = 4, d = 2, f = 2;
	}
	else {
		i = 2, d = 1, f = 5;
	}
}

int chooseTransaction() {
	int number = rand() % 8;
	if (number < i) return 1;
	else if (number < i + d) return 2;
	else return 3;
}

void printType(datas data[], int size, string name) {
	ofstream output(name + ".txt");
	for (int i = 1; i <= size; i++) {
		output << data[i].load << ",";
	}
	output << endl << endl << endl;
	for (int i = 1; i <= size; i++) {
		output << data[i].probe<<",";
	}
	output.close();
}

int main() {
	srand(seed);
	HashTable table(notFound, M);
	static datas suc_Ins[M + 1]; static  datas suc_Del[M + 1]; static  datas fail_Del[M + 1]; static  datas suc_Find[M + 1]; static  datas fail_Find[M + 1];
	int numSeed = M * 10;
	int nOfTransactions = 0;
	int nofsuc_Ins = 0, noffail_Ins = 0, nofsuc_Del = 0, noffail_Del = 0, nofsuc_Find = 0, noffail_Find = 0;
	int tableSize = table.getSize();
	while (!table.isFull()&&nOfTransactions!=1000000) {
		int randNum = rand() % numSeed;
		int type = chooseTransaction();
		int probe = 0;
		double currentload;
		bool isSuccess;
		++nOfTransactions;
		if (type == 1) {
			isSuccess = table.insert(randNum, probe);
			currentload = table.getCurrent()*1.0 / tableSize;
			if (isSuccess) {
				++nofsuc_Ins;
				suc_Ins[nofsuc_Ins].load = currentload, suc_Ins[nofsuc_Ins].probe = probe;
			}
			else {
				++noffail_Ins;
				fail_Ins[noffail_Ins].load = currentload, fail_Ins[noffail_Ins].probe = probe;
			}
		}
		
		
		else if (type == 2) {
			isSuccess = table.remove(randNum, probe);
			currentload = table.getCurrent()*1.0 / tableSize;
			if (isSuccess) {
				++nofsuc_Del;
				suc_Del[nofsuc_Del].load = currentload, suc_Del[nofsuc_Del].probe = probe;
			}
			else {
				++noffail_Del;
				fail_Del[noffail_Del].load = currentload, fail_Del[noffail_Del].probe = probe;
			}
		}
		
		
		else if (type == 3) {
			isSuccess = table.find(randNum, probe);
			currentload = table.getCurrent()*1.0 / tableSize;
			if (isSuccess) {
				++nofsuc_Find;
				suc_Find[nofsuc_Find].load = currentload, suc_Find[nofsuc_Find].probe = probe;
			}
			else {
				++noffail_Find;
				fail_Find[noffail_Find].load = currentload, fail_Find[noffail_Find].probe = probe;
			}
		}
	}

	printType(suc_Ins, nofsuc_Ins, "successful_Insert");
	printType(fail_Ins, noffail_Ins, "failed_Insert");
	printType(suc_Del, nofsuc_Del, "successful_Delete");
	printType(fail_Del, noffail_Del, "failed_Delete");
	printType(suc_Find, nofsuc_Find, "successful_Find");
	printType(fail_Find, noffail_Find, "failed_Find");

	return 0;
}