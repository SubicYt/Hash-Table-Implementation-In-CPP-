#include <iostream>
#include <list>

class HashTable {
private:
	static const int HashGroups = 10; //Num of hash buckets
	std::list<std::pair<int, std::string>> HashTable[HashGroups];

public:
	bool isEmpty();
	int hashFunction(int key);
	void add_item(int key, std::string value);
	void remove_item(int key);
	void printTable();
};

bool HashTable::isEmpty() {
	int sum{}; //initialized to zero. 
	for (int i = 0; i < HashGroups; i++) { //Iterate through the hashTable buckets
		sum += HashTable[i].size(); //The sum of size of the bucket
	}
	if (sum == 0) {
		return true; //Sum is zero so the Hash Table is empty
	}
	else {
		return false; //sum is not zero, hash table contains elements
	}
}

int HashTable::hashFunction(int key) {
	//create the hash funciton using the modulus operator
	int HashValue = key % HashGroups;
	return HashValue; // return the remainder of key number and the number of hash buckets (10). Ex: 905 %10 = bucket 5
}

void HashTable::add_item(int key, std::string value) {
	int HashValue = hashFunction(key); //get the bucket for the item;
	auto& bucket = HashTable[HashValue]; 
	auto bucket_iterator = begin(bucket);
	bool keyExists = false;
	/*
	* 
	* for (; bucket_iterator != end(bucket); bucket_iterator++) {
		if (bucket_iterator->first == key) {
			keyExists = true;
			bucket_iterator->second = value;
			std::cout << "Key has been replaced ";
			break;
		}
	}
	if (!keyExists) {
		bucket.emplace_back(key, value);
	
	essentially what this block of code implemented below is doing is checking to see if 
	a key we are trying to add already exists. 
	If it does then we are replace the existing value with our new one and then breaking out of the loop
	It is important to know that each bucket is a respective linkedlist and we are emplacing_back(key, value) pairs
	We are iterating over each respective bucket at location hash value to see if the key is already there. 
	}
	*/
	for (; bucket_iterator != end(bucket); bucket_iterator++) {
		if (bucket_iterator->first == key) {
			keyExists = true;
			bucket_iterator->second = value;
			std::cout << "Key has been replaced ";
			break;
		}
	}
	if (!keyExists) {
		bucket.emplace_back(key, value);
	}
}

void HashTable::remove_item(int key) {
	int HashValue = hashFunction(key); //get the bucket for the item;
	auto& bucket = HashTable[HashValue];
	auto bucket_iterator = begin(bucket);
	bool keyExists = false;

	for (; bucket_iterator != end(bucket); bucket_iterator++) {
		if (bucket_iterator->first == key) {
			keyExists = true;
			bucket_iterator = bucket.erase(bucket_iterator);
			std::cout << "Key has been removed" << std::endl;
			break;
		}
	}
	if (!keyExists) {
		std::cout << "Key not found" << std::endl;
	}
}

void HashTable::printTable() {
	for (int i{}; i < HashGroups; i++) {
		if (HashTable[i].size() == 0) {
			continue;
		}
		else {
			auto bucket_iterator = HashTable[i].begin();
			for (; bucket_iterator!=HashTable[i].end(); bucket_iterator++) {
				std::cout << "element: " << bucket_iterator->second << std::endl; 
				// -> second prints the value (second item in pair)l
			}
		}
	}
}

int main() {
	//Test emptiness
	HashTable H1; 
	if (H1.isEmpty()) {
		std::cout << "Correct- is empty" << std::endl;
	}
	else {
		std::cout << "fix method";
	}

	//Populate HashTable.
	std::cout << "--------Testing add_item--------" << std::endl;
	HashTable H2;
	H2.add_item(32, "Henry");
	H2.add_item(30, "Jane");
	H2.add_item(6, "Kenny");
	H2.printTable();

	std::cout << "--------Testing remove_item--------" << std::endl;

	HashTable H3;
	H3.add_item(32, "Henry");
	H3.add_item(30, "Jane");
	H3.add_item(6, "Kenny");
	H3.remove_item(6);
	H3.remove_item(9);
	H3.printTable();
}
