#pragma once
#include <vector>
using namespace std;
class HashTable{
public:
	explicit HashTable(const int & notFound, int size = 101);
	HashTable(const HashTable & rhs)
		: ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND),
		arr(rhs.arr), currentSize(rhs.currentSize), load(rhs.load) {}
	bool find(const int & x, int & probe) const;
	bool isFull() const;
	int getCurrent();
	int getSize();
	void makeEmpty();
	bool insert(const int & x, int & probe);
	bool remove(const int & x, int & probe);

	const HashTable & operator=(const HashTable & rhs);

	enum EntryType { ACTIVE, EMPTY, DELETED };
private:
	struct HashEntry{
		int element;
		EntryType info;

		HashEntry(const int & e = int(), EntryType i = EMPTY)
			: element(e), info(i) { }
	};
	vector<HashEntry> arr;
	int currentSize;
	int load;
	const int ITEM_NOT_FOUND;
	bool isActive(int currentPos) const;
	int findPos(const int & x, int & probe) const;
	int findInsert(const int & x, int & probe) const;
};

bool isPrime(int number) {

	if (number == 2 || number == 3)
		return true;

	if (number % 2 == 0 || number % 3 == 0)
		return false;

	int divisor = 6;
	while (divisor * divisor - 2 * divisor + 1 <= number)
	{

		if (number % (divisor - 1) == 0)
			return false;

		if (number % (divisor + 1) == 0)
			return false;

		divisor += 6;

	}

	return true;

}

int nextPrime(int a) {

	while (!isPrime(a))
	{
		++a;
	}
	return a;

}

int hashVal(int num, int tableSize) {
	return num%tableSize;
}

HashTable::HashTable(const int & notFound, int size)
	: currentSize(nextPrime(size)),ITEM_NOT_FOUND(notFound), arr(nextPrime(size)), load(0) {
	makeEmpty();
}

int HashTable::findPos(const int & x, int & probe) const {
	probe = 0;
	int currentPos = hashVal(x, arr.size());

	while (arr[currentPos].info != EMPTY && arr[currentPos].element != x) {
		++probe;
		if (++currentPos >= arr.size())
			currentPos -= arr.size();
		if (probe > currentSize) {
			return currentPos;
		}
	}
	return currentPos;
}

int HashTable::findInsert(const int & x, int & probe) const {
	probe = 0;
	int currentPos = hashVal(x, arr.size());
	while (arr[currentPos].info == ACTIVE && arr[currentPos].element != x) {
		++probe;
		if (++currentPos >= arr.size())
			currentPos -= arr.size();
	}
	return currentPos;
}

bool HashTable::isActive(int currentPos) const {
	return arr[currentPos].info == ACTIVE;
}

bool HashTable::remove(const int & x, int & probe) {
	int currentPos = findPos(x,probe);
	if (isActive(currentPos)){
		arr[currentPos].info = DELETED;
		load--;
		return true;
	}
	return false;
}

bool HashTable::find(const int & x, int & probe) const {

	int currentPos = findPos(x, probe);
	if (isActive(currentPos))
		return true;
	return false;
}

bool HashTable::insert(const int & x, int & probe) {
	probe = 0;
	int currentPos = findInsert(x,probe);
	if (isActive(currentPos)){
		return false;
	}
	arr[currentPos] = HashEntry(x, ACTIVE);
	load++;
	return true;
}

void HashTable::makeEmpty() {
	vector<HashEntry> vec(nextPrime(currentSize));
	arr = vec;

}

bool HashTable::isFull() const {
	return currentSize == (load+1);
}

int HashTable::getCurrent() {
	return load;
}

int HashTable::getSize() {
	return arr.size();
}