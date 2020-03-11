#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <istream>

using namespace std;
//txt leri unutma, ayrica prevleri ayarla
int main() {
	ifstream input("compout.txt");
	
	bool isExist[4096];
	string elementAt[4096];
	int encoded, start=255, prev;
	
	for (int i = 0; i < 4096; i++) {
		isExist[i] = false;
	}
	for (int i = 0; i < 256; i++) {
		isExist[i] = true;
		elementAt[i] = i;
	}

	ofstream output("decompout.txt");
	bool isFirst = true;
	while (input >> encoded) {
		if (isFirst) {
			prev = encoded;
			output << elementAt[prev];
			isFirst = false;
		}

		else {
			if (isExist[encoded] == false) {
				++start;
				string prevElement = elementAt[prev] + elementAt[prev][0];
				elementAt[start] = prevElement;
				output << prevElement;
				isExist[start] = true;
			}
			else {
				++start;
				string nextElement = elementAt[prev] + elementAt[encoded][0];
				elementAt[start] = nextElement;
				isExist[start] = true;
				output << elementAt[encoded];
			}
		}

		prev = encoded;
	}

}