#include "HashMapVE.h"

HashMapVE::HashMapVE(int tbSz) {
	if (tbSz == 0)
		tbSz = DEFAULT_TABLE_SIZE;
	initialize(tbSz);
}


ValueEntry * HashMapVE::get(string key) {
	size_t hashKey = hash<string>()(key);
	int hash = hashKey  % tableSize;

	if (table[hash] == NULL)
		return NULL;

	if (table[hash]->getKey()._Equal(key))
		return table[hash];

	ValueEntry * current = table[hash];
	while (current != NULL) {
		if (current->getKey()._Equal(key))
			return current;
		current = current->getNext();
	}

	return current;

}


void HashMapVE::put(string key) {
	size_t hashKey = hash<string>()(key);

	int hash = hashKey % tableSize;
	if (table[hash] != NULL) {
		if (!table[hash]->getKey()._Equal(key)) {
			/*if it is a hashkey collission, the collisions is handled*/
			handleCollision(table[hash], key);
		}
	}
	else {
		table[hash] = new ValueEntry(key,0);
		NO_OF_ENTRIES++;
	}

	/*If the number of entries have exceeded our density limit, we rehash.*/
	if ((tableSize - NO_OF_ENTRIES) <= LIMIT) {
		//print();
		//cout << "Rehashing docuemnts.." << endl;
		reHashMap();
	}
}

void HashMapVE::handleCollision(ValueEntry * current, string key) {
	bool keyExist = false;
	int numberOfCol = 0;

	/*walk down the collision chain, compare, if value does not exist then create.*/
	while (current != NULL) {
		numberOfCol++;
		if (current->getKey()._Equal(key)) {
			keyExist = true;
			break;
		}
		if (current->getNext() == NULL)
			break;
		current = current->getNext();
	}

	if (!keyExist) {
		current->setNext(new ValueEntry(key, 0));
		NO_OF_ENTRIES++;
	}
	if (numberOfCol >= MAX_NO_OF_COLLISIONS)
		MAX_NO_OF_COLLISIONS = numberOfCol;

	/*TODO : If HIGHEST_NO_OF_COLLISIONS is bigger than MAX_NO_OF_COLLISIONS, then expand hashtable and rehash everything*/
}


void HashMapVE::reHashMap() {
	/*Expanding the old table size by 2*/
	int newTableSize = 2 * tableSize;
	HashMapVE * newT = new HashMapVE(newTableSize);

	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {

			/*Recursing and conituning in the list of collissions*/
			ValueEntry * currentH = table[i];
			while (currentH != NULL) {
				newT->put(currentH->getKey());

				if (currentH->getNext() == NULL)
					break;

				currentH = currentH->getNext();
			}
		}
	}

	/*Delete the old table and point the new table created in the heap to the old table*/
	for (int i = 0; i < tableSize; i++) {		
		delete table[i];
	}
	delete table;

	initialize(newTableSize);
	table = newT->getTable();
	MAX_NO_OF_COLLISIONS = newT->MAX_NO_OF_COLLISIONS;
}

int HashMapVE::getTableSize() {
	return tableSize;
}

void HashMapVE::initialize(int tbSz) {
	table = new ValueEntry*[tbSz];
	for (int i = 0; i < tbSz; i++) {
		table[i] = NULL;
	}
	tableSize = tbSz;
	LIMIT = tableSize * (1-DENSITY_THRESHOLD);
	MAX_NO_OF_COLLISIONS = 0;
}

void HashMapVE::print() {
	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {
			
			ValueEntry * current = table[i];
			while (current != NULL) {
				cout << current->getKey() << endl;
				
				if (current->getNext() == NULL)
					break;

				current = current->getNext();
			}		
		}		
	}
}

ValueEntry ** HashMapVE::getTable() {
	return table;
}
HashMapVE::~HashMapVE() {
	if (tableSize == 0)
		return;

	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {
			delete table[i];
		}
	}
	delete[] table;
}