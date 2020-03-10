#include <vector>
#include <iostream>
#pragma once
using namespace std;
//Furkan Ergün 24083

template<class filterType, class elementType>
class BloomFilter{
	private:
		int totalBits, k, needed;
		int as[2], bs[2];
		vector<filterType> filters; //vector of filters which the bits will be stored
		string BloomFilter::to_str(const elementType& obj); //helper
		dasdas;
	
	public:
		BloomFilter(int bits, int k, int as[2], int bs[2]);
		int BloomFilter::hash(string x_str, int index, int* as, int* bs);
		void BloomFilter::addElement(elementType element);
		bool BloomFilter::checkExist(elementType element);
		void BloomFilter::printFilter();
};