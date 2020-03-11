#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
/*
Furkan Ergün
***24083***
*/


struct peoples {
	peoples() 
	{}
	peoples(string name, int money, peoples* ptr)
		:name(name), money(money)
	{
		nextP = ptr;
	}
	int money = 0;
	string name;
	peoples* nextP = nullptr;
};
/*It is been told that iterating through linked lists are not efficient enough.
So I wanted to create a struct just in order to store peoples in the blockchain
and manipulate their money in the way of transactions.*/
struct inputNode {
	inputNode()
	{
		nextI = nullptr;
	}
	inputNode(int transactionId, int outputLocation, inputNode* ptr)
		:transactionId(transactionId), outputLocation(outputLocation)
	{
		nextI = ptr;
	}
	int transactionId;
	int outputLocation;
	inputNode* nextI;
};
struct outputNode {
	outputNode()
	{
		nextO = nullptr;
	}
	outputNode(int amount, string sendTo, outputNode* ptr)
		:amount(amount), sendTo(sendTo)
	{
		nextO = ptr;
	}
	int amount;
	string sendTo;
	outputNode* nextO;
};
struct transactionNode {
	transactionNode()
	{}
	transactionNode(int tid, string owner, int pow, int hval, transactionNode* next)
		:tid(tid), owner(owner), PoW(pow), hval(hval), nextT(next)
	{}
	int tid;
	string owner;
	int PoW;
	int hval;
	inputNode* inputList;
	outputNode* outputList;
	transactionNode* nextT;
};
/*
I don't wanna explain these two as they are explained in the pdf
*/



int hashfun(transactionNode *newT, int prev_hval, int PoW) {
	int hval = (prev_hval + 1111) * (PoW + 1111);
	outputNode * outPtr = newT->outputList;
	while (outPtr) {
		hval += outPtr->amount;
		string str = outPtr->sendTo;
		for (int i = 0; i < str.length(); i++) {
			hval += ((int)str[i]);
		}
		outPtr = outPtr->nextO;
	}
	inputNode * inPtr = newT->inputList;
	while (inPtr) {
		hval += inPtr->transactionId;
		hval += inPtr->outputLocation;
		inPtr = inPtr->nextI;
	}
	return (hval % 137);
}
int mine(transactionNode *newT, transactionNode* bchain, int& hval, int& PoW, int threshold) {
	transactionNode* tmp = bchain;
	int prev_hval = 0;
	while (tmp) {
		prev_hval = tmp->hval;
		tmp = tmp->nextT;
	}
	PoW = 1;
	while ((hval = hashfun(newT, prev_hval, PoW)) >= threshold) {
		cout << "Trying to find a hash value..." << "hash: " << hval << " PoW: " << PoW <<
			endl;
		PoW++;
	}
	return PoW;
}


int moneyFinder(transactionNode* head,int tid, int location){
	//This function returns the money in the specific output so it can be used once.
	transactionNode* temp = head;
	while (temp != nullptr) {
		if (tid == temp->tid) {
			outputNode* tempO = temp->outputList;
			for (int i = 1; i < location; i++) {
				tempO = tempO->nextO;
			}
			return tempO->amount;
		}
		temp = temp->nextT;
	}
	return 0;
}
bool ownerChecker(transactionNode* head, string owner, int id, int location){
	//This function iterates through all outputs to see if the owner for a input is valid or not
	transactionNode* temp = head;
	bool isValid = false;
	while (temp != nullptr) {
		if (temp->tid == id) {
			outputNode* tempO = temp->outputList;
			for (int i = 1; i < location; i++) {
				if (tempO == nullptr) {
					return false;
				}
				tempO = tempO->nextO;
			}
			if (tempO->sendTo == owner) {
				return true;
				isValid = true;
		}
		}
		temp = temp->nextT;
	}
	return isValid;
}
bool transactionChecker(transactionNode* head, int id, int location) {
	//This function checks if a input used before as a another input
	bool isValid = true;
	transactionNode* temp = head;
	while (temp != nullptr) {
		inputNode* tempI = temp->inputList;
		while (tempI != nullptr) {
			if (tempI->transactionId == id) {
				if (tempI->outputLocation == location)
					isValid = false;
			}

		tempI = tempI->nextI;
		}
	temp = temp->nextT;
	}
	return isValid;
}
void addtoEnd(outputNode* &head, int amount, string sendTo) {
	//Adds an outputnode to the head, if the head is nullptr this function changes head, else adds the outputnode to the end
	outputNode* ptr = head;
	outputNode *temp = new outputNode(amount, sendTo, nullptr);
	if (head == nullptr)
	{
		head = temp;
	}
	else
	{
		while (ptr->nextO != nullptr)
		{
			ptr = ptr->nextO;
		}
		ptr->nextO = temp;
	}
}
void addtoEnd(inputNode* &head, int transactionId, int outputLocation) {
	//Adds an inputNode to the head, if the head is nullptr this function changes head, else adds the inputNode to the end
	inputNode* ptr = head;
	inputNode *temp = new inputNode(transactionId, outputLocation, nullptr);
	if (head == nullptr)
	{
		head = temp;
	}
	else
	{
		while (ptr->nextI != nullptr)
		{
			ptr = ptr->nextI;
		}
		ptr->nextI = temp;
	}

}
void addtoEnd(peoples* &head, string name, int money) {
	//Adds an peoples to the head, if the head is nullptr this function changes head, else adds the peoples to the end
	peoples* ptr = head;
	peoples *temp = new peoples(name, money, nullptr);
	if (head == nullptr)
	{
		head = temp;
	}
	else
	{
		while (ptr->nextP != nullptr)
		{
			ptr = ptr->nextP;
		}
		ptr->nextP = temp;
	}
}
void addtoEnd(transactionNode*& head, transactionNode*& addOn) {
	//Adds an transactionNode to the head, if the head is nullptr this function changes head, else adds the transactionNode to the end
	addOn->nextT = nullptr;
	transactionNode* temp = head;
	if (temp == nullptr) {
		head = addOn;
	}
	else {
		while (temp->nextT != nullptr) {
			temp = temp->nextT;
		}
		temp->nextT = addOn;
	}
}
bool changeMoney(peoples* head, string name, int money) {
	//Changes the money of a people. Very effective against iterating through the linked lists.
	peoples *temp = head;
	while (temp->name != name) {
		temp = temp->nextP;
	}
	if (temp->name == name) {
		temp->money += money;
		return true;
	}
	return false;
}
void printBlockchain(transactionNode* head) {
	//Iterates through and prints the blockchain. Not much of a logic here, just "cout"'s
	transactionNode *temp = head;
	while (temp != nullptr) {
		cout << "Transaction id:" << temp->tid << " owner:" << temp->owner << " hash:" << temp->hval << " PoW:" << temp->PoW << endl << "Input list" << endl;
		if (temp->inputList == nullptr)
			cout << endl;
		else {
			inputNode* tempI = temp->inputList;
			while (tempI != nullptr) {
				cout << "Tid:" << tempI->transactionId << " location:" << tempI->outputLocation << " ";
				tempI = tempI->nextI;
			}
			cout << endl;
		}
		cout << "Output list" << endl;
		outputNode* tempO = temp->outputList;
		while (tempO != nullptr) {
			cout << "Amount:" << tempO->amount << " send to:" << tempO->sendTo << endl;
			tempO = tempO->nextO;
		}
		cout << endl;
		temp = temp->nextT;
	}
}
void printRemainingMoney(transactionNode* blockchain, peoples* head) {
	//First takes the name of the person whom remaining money is needed, then finds the person from the
	//peoples linked list and prints his money
	string owner;
	cout << "Write the name you want to search :" << endl;
	cin >> owner;
	peoples* temp = head;
	while (temp->name != owner) {
		temp = temp->nextP;
		if (temp == nullptr)
			break;
	}
	if (temp != nullptr)
		cout << owner << "'s wallet: " << temp->money << endl;
	else{
		cout << owner << "'s wallet: 0" << endl;
	}
}
void addTransaction(transactionNode* blockchain, peoples* phead){
	static int tid = 1; //Tid starts with one and increases just before every transaction(so starts with two because first transaction had been done manually
	int totalInput = 0; //Total amount of input(money)
	string owner, inputList, input="";
	cout << "Input the owner of the transaction :" << endl;
	cin >> owner;
	cout << "Write the input list in form of" << endl << "'transactionId_1 outLocation_1 transactionId_2 outLocation_2 #'" << endl << "put # after all the inputs finish:" << endl;
	while (true) {
		cin >> input;
		if (input == "#")
			break;
		inputList += input + " "; //Will be used in stringstream later
	}
	inputList = inputList.substr(0, inputList.length() - 1); //Last blank corrupts the work I done below
	istringstream listGrbg(inputList);
	string strId, strLocation;
	int inputlines=0;
	string GARBAGE;	//In order to store how many date in the stringstream I have to iterate through it once before storing the data. So this variable is pretty much neglectible
	while (!listGrbg.eof()) {
		inputlines++;
		listGrbg >> GARBAGE;
	}
	int* ptrInput = new int[inputlines];	
	istringstream list(inputList);
	int i = 0;
	int id, location;
	while (!list.eof()) {
		list >> id >> location;
		ptrInput[i] = id;	//Storing the id 
		i++;
		ptrInput[i] = location;	//Storing the location afterwards the id
		i++;
		totalInput += moneyFinder(blockchain, ptrInput[i - 2], ptrInput[i-1]); //Calculating the total money
	}

	//Output process is almost same with input process.
	
	int outputlines = 0;
	cout << "Write the output list in form of" << endl << "'amount_1 sentTo_1 amount_2 sentTo_2 #'" << endl << "put # after all the inputs finish:" << endl;
	string output, outputList;
	while (true) {
		cin >> output;
		if (output == "#")
			break;
		outputList += output + " "; //Will be used in stringstream later
	}
	outputList = outputList.substr(0, outputList.length() - 1);
	istringstream oListGrbg(outputList);
	while (!oListGrbg.eof()) {
		outputlines++;			//Necessary in order to not getting lost in output pointers
		oListGrbg >> GARBAGE; //In order to store how many date in the stringstream I have to iterate through it once before storing the data. So this variable is pretty much neglectible
	}
	int* ptrOutputAmount = new int[outputlines / 2];
	string* ptrOutputOwner = new string[outputlines / 2];
	istringstream oList(outputList);
	int amount;
	i = 0;
	string oOwner;
	int totalOutput = 0;
	while (!oList.eof()) {
		oList >> amount >> oOwner;
		ptrOutputAmount[i] = amount;	//Storing the amount which will be sent
		totalOutput += amount;			//totalOutput is different than the totalinput as one is the money owner have one is the money which will be sent
		ptrOutputOwner[i] = oOwner;		//Storing the name of receiver of the money
		i++;
	}
	bool isOwner = false, isTotal = false, isDouble = false;
	for (int i = 0; i < inputlines; i += 2) {
		if (!ownerChecker(blockchain, owner, ptrInput[i], ptrInput[i + 1])) {
			isOwner = true;	//If there is a owner problem
			break;
		}
		else if (!transactionChecker(blockchain, ptrInput[i], ptrInput[i + 1])) {
			isDouble = true;	//If there is a double spending problem
			break;
		}
		else if (totalInput < totalOutput) {
			isTotal = true;	//Problem is pretty obvious. Spending more than in the hands
			break;
		}
	}
	//Below here proper syntaxes for the errors
	if (isOwner) {
		cout << "Invalid T: input owner is not right!" << endl;
		return;
	}
	else if (isDouble) {
		cout << "Invalid T: Double spending!" << endl;
		return;
	}
	else if (isTotal) {
		cout << "Invalid T: total output > total input!" << endl;
		return;
	}
	tid++;	//Tid is getting increased as has been told before
	inputNode* newI = new inputNode;	//This will not be deleted as deleting this corrupts the program flow
	newI = nullptr;
	outputNode* newO = new outputNode;	//This will not be deleted as deleting this corrupts the program flow
	newO = nullptr;
	for (int i = 0; i < inputlines; i+=2) {
		addtoEnd(newI, ptrInput[i], ptrInput[i + 1]);	//Arranging the input linked list
	}
	for (int i = 0; i < outputlines / 2; i++ ) {
		addtoEnd(newO, ptrOutputAmount[i], ptrOutputOwner[i]);	//Arranging the output linked list
		changeMoney(phead, ptrOutputOwner[i], ptrOutputAmount[i]);	//Never forget to update the money as it will be used later
	}

	int remaining = totalInput - totalOutput;
	if (remaining>0)
		addtoEnd(newO, remaining, owner);	//Owner's remaining money is returned to him as a output

	transactionNode* newT = new transactionNode;	//This will not be deleted as deleting this corrupts the program flow
	newT->inputList = newI,	newT->outputList = newO, newT->owner = owner, newT->tid = tid;
	int hval, PoW;
	mine(newT, blockchain, hval, PoW, 10);
	newT->hval = hval, newT->PoW = PoW;
	addtoEnd(blockchain, newT);
	changeMoney(phead, owner, totalOutput*-1);	//Sender's money changes as he/she sends money
	cout << "New transaction added successfuly!" << endl;	//At last ...

}



int main() {
	ifstream input("input.txt");	//first input have to be taken from this text.
	string owner;
	int pow, hval;
	input >> owner >> hval >> pow;	//Making the proper reading from the input.txt
	transactionNode* blockchain = new transactionNode;
	blockchain->hval = hval, blockchain->PoW = pow, blockchain->inputList = nullptr, blockchain->nextT = nullptr, blockchain->owner = owner, blockchain->tid = 1, blockchain->outputList = nullptr; //Seems messy, yet consistent.
	peoples *phead=nullptr;	//Creating the persons linked list
	while (!input.eof()) {
		// Making the proper reading and creating the head of transactionNode
		// Also arranging the peoples linked list
		string receiver;
		int amount;
		input >> amount >> receiver;
		addtoEnd(phead, receiver, amount);
		addtoEnd(blockchain->outputList, amount, receiver);
	}

	while (true)
	{
		cout << endl;
		cout << "******************************************************" << endl
			<< "***** 0 - EXIT PROGRAM ****" << endl
			<< "***** 1 - PRINT BLOCKCHAIN ****" << endl
			<< "***** 2 - PRINT REMAINING MONEY OF A USER ****" << endl
			<< "***** 3 - ADD A TRANSACTION ****" << endl
			<< "****************************************************" << endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3):"; 
		cin>>option;
			switch (option)
			{
			case 0:
				cout << "PROGRAM EXITING ... " << endl;
				system("pause");
				exit(0);
			case 1:
				printBlockchain(blockchain);
				break;
			case 2:
				printRemainingMoney(blockchain, phead);
				break;
			case 3:
				addTransaction(blockchain, phead);
				break;
			default:
				cout << "INVALID OPTION!!! Try again" << endl;
			}//switch
	}//while (true)

}