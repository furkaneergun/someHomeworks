#include <iostream>
#include <string>
#include "Bst.hpp"
#include <istream>
#include <sstream>
#include <fstream>

using namespace std;

int main() {
	const int notFound = -99;
	int code = 255;
	BinarySearchTree locations(notFound);
	
	ifstream input("compin.txt");
	input >> noskipws;

	string prev, p="", word="";
	int count=0;
	char c;

	ofstream output("compout.txt");

	while (input.get(c)) {
		p += c;
		if (locations.find(p) == notFound) {
			int outputNum;
			int encoded;
			if (prev.length() == 1)
				outputNum = prev[0];
			else
				outputNum = locations.find(prev);

			locations.insert(code, p);
			code++;
			p = c;

			if(outputNum!=notFound)	output << outputNum << " ";
		}
		prev = p;
	}

	output.close();
	return 0;
}