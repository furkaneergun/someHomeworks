#include "BloomFilter.h"
#include <ostream>
#include <iostream>
#include <string>
#include <sstream>
#pragma once
using namespace std;

//Furkan Ergün 24083

template<class filterType, class elementType>
string BloomFilter<filterType, elementType>::to_str(const elementType & obj)
{
	ostringstream oss;
	oss << obj;
	return oss.str();
}

template<class filterType, class elementType>
BloomFilter<filterType, elementType>::BloomFilter(int bits, int k, int as[2], int bs[2])
{
	totalBits = bits, this->k = k, this->as[0] = as[0], this->bs[0] = bs[0], this->as[1] = as[1], this->bs[1] = bs[1];	//Assigning the values
	double dble;
	int integer;
	integer = bits / sizeof(filterType) / 8;
	dble = bits / sizeof(filterType);
	dble /= 8;
	if (integer != dble)  integer++; //If the number of required bit is not integer multiply of a 1 2 4 or 8, then one more element of the type of filter is required
	needed = integer;	//Needed is integer+1 if the condition is met else if totalbit=k(1 or 2 or 4 or 8) needed is integer
	for (int i = 0; i < needed; i++) {
		filterType object = 0;	//Creating an empty memory
		filters.push_back(object);	//Pushing the empty memories n times 0 as n is the size of filtertype
	}
}

template<class filterType, class elementType>
int BloomFilter<filterType, elementType>::hash(string x_str, int index, int* as, int* bs) {
	unsigned int hash = 0;
	for (int i = 0; i < x_str.length(); i++) {
		hash ^= (x_str[i] * 899809363);
	}
	hash = (as[index] * hash) + bs[index];
	hash = hash % (totalBits);	//getSize()
	return hash;
}

template<class filterType, class elementType>
void BloomFilter<filterType, elementType>::addElement(elementType element) {
	int size_element = sizeof(filterType) * 8;
	for (int i = 0; i < k; i++) {	//Invoking the hash function k times
		int theHash=hash(to_str(element), i, as, bs);	
		int nth = 0;	// location=Ax+b; n is here represent A
		while (!(theHash < size_element)) {
			nth++;
			theHash -= size_element;	//At the end theHash will represent the b in Ax+b
		}
		if (size_element == 64) {	//If the size is bigger than 32 the 0x1 does not work(implicit casting), As I could create an 1 object type of filtertype, I did not wanted to do that.
			long long num = 1;	//0x1 in 64bit
			filters[nth] |= num << theHash;	//Left shifting the 1 by the b in Ax+b and inserting the 1 into the bth location of Anth element
		}
		else {
		filters[nth] |= 0x1 << theHash;	//Same thing above with the filters which size is equal or smaller than 32;
		}
	}
}

template<class filterType, class elementType>
bool BloomFilter<filterType, elementType>::checkExist(elementType element){
	//Actually, almost same things with the addElement func. Only difference is this function checks whether the location is 1 or 0 rather than inserting the 1;
	//Could have used an helper function for other attributes but did not wanted to violate the hw rules
	int size_element = sizeof(filterType) * 8;
	for (int i = 0; i < k; i++) {
		int theHash = hash(to_str(element), i, as, bs);
		int nth = 0;
		while (!(theHash < size_element)) {
			nth++;
			theHash -= size_element;
		}
		if (!((1 << theHash) & filters[nth])) return false;	//if there is any 0 in specific location
	}
	return true;	//if everything is ok
}

template<class filterType, class elementType>
void BloomFilter<filterType, elementType>::printFilter(){
	int size = 8 * sizeof(filterType);
	int first = (needed * size) - totalBits;	//If there is any location which is not integer multiply of 1,2,4 or 8 the process is different for the last filter since not all of it's bits are used
	first = size - first;	//
	if (first!=0){	//If there is an filter with not all of it's bits are used, then it should be used separetely
		for (int i=0; i<first; i++) {	//Starting not with most significant bit of the last filter. It starts with the first used bit of the last filter. 
			cout << ((filters[needed - 1] >> i) & 1);
		}
		for (int j = needed - 2; j >= 0; j--) {	//Then the others can be done as the classical way
			for (int i = size-1; i >= 0; i--)
				cout << ((filters[j] >> i) & 1);
		}
	}
	else {	//bitCount is integer multiply of 1,2,4 or 8;
		for (int j = needed - 1; j >= 0; j--) {
			for (int i = size-1; i >= 0; i--)
				std::cout << ((filters[j] >> i) & 1);
		}
	}
}

