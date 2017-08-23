#include "HashMapHE.h"
#include "HashFunctions.h"

HashMapHE::HashMapHE(int tbSz) {
	if (tbSz == 0)
		tbSz = DEFAULT_TABLE_SIZE;
	initialize(tbSz);
}


HashEntry * HashMapHE::get(string key) {
	size_t hashKey = hash<string>()(key);
	int hash = hashKey  % tableSize;

	if (table[hash] == NULL)
		return NULL;

	if (table[hash]->getKey()._Equal(key))
		return table[hash];

	HashEntry * current = table[hash];
	while (current != NULL) {
		if (current->getKey()._Equal(key))
			return current;
		current = current->getNext();
	}

	return current;

}



void HashMapHE::put(string key, string dt) {
	if (empty)
		empty = false;

	size_t hashKey = hash<string>()(key);
	//unsigned int hashKey = HashFunctions::RSHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::JSHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::PJWHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::SDBMHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::DJBHash(key.c_str(), key.length());

	int hash = hashKey % tableSize;
	if (table[hash] != NULL) {
		/*if it is a hashkey collission, the collisions is handled*/
		if (!table[hash]->getKey()._Equal(key)) {
			handleCollision(table[hash], key, dt);
		}
		else {
			/*if theres no hashkey collision, we simply want to update the document list*/
			table[hash]->getValueEntries()->put(dt);
		}
	}
	else {
		table[hash] = new HashEntry(key, dt, 0);
		NO_OF_ENTRIES++;
	}

	/*If the number of entries have exceeded our density limit, we rehash.*/
	if ((tableSize - NO_OF_ENTRIES) <= LIMIT) {
		cout << "Rehashing ....... " << endl;
		reHashMap();
	}
}

void HashMapHE::handleCollision(HashEntry * current, string key, string dt) {
	bool keyExist = false;
	int numberOfCol = 0;
	/*walk down the collision chain, compare, if value does not exist then create.*/
	while (current != NULL) {
		numberOfCol++;
		if (current->getKey()._Equal(key)) {
			/*Insert document to the document list*/
			current->getValueEntries()->put(dt);
			keyExist = true;
			break;
		}
		if (current->getNext() == NULL)
			break;

		current = current->getNext();
	}

	if (!keyExist) {
		current->setNext(new HashEntry(key, dt, 0));
		NO_OF_ENTRIES++;
	}
	if (numberOfCol >= MAX_NO_OF_COLLISIONS)
		MAX_NO_OF_COLLISIONS = numberOfCol;

	//TODO : If HIGHEST_NO_OF_COLLISIONS is bigger than MAX_NO_OF_COLLISIONS, then expand hashtable and rehash everything*/
}


void HashMapHE::InsertReHashValueEntries(HashMapHE * newT, HashMapVE * oldEntries, string key) {
	int size = oldEntries->getTableSize();
	for (int i = 0; i < size; i++) {
		if (oldEntries->getTable()[i] != NULL) {

			/*Inserting value entries again*/
			ValueEntry * current = oldEntries->getTable()[i];
			while (current != NULL) {
				newT->put(key, current->getKey());
				/*Updating the number of occurences*/
				newT->get(key)->getValueEntries()->get(current->getKey())->setOcc(current->getOcc());
				if (current->getNext() == NULL)
					break;
				current = current->getNext();
			}

		}
	}
}

void HashMapHE::reHashMap() {

	/*Expanding the old table size by 2*/
	int newTableSize = 2 * tableSize;
	HashMapHE * newT = new HashMapHE(newTableSize);

	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {

			if (table[i]->getKey() == "algae") {
				int j = 0;
			}

			/*Iterating through the list of collissions*/
			HashEntry * currentH = table[i];
			while (currentH != NULL) {
				InsertReHashValueEntries(newT, currentH->getValueEntries(), currentH->getKey());
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
	delete[] table;

	initialize(newTableSize);
	table = newT->getTable();
	MAX_NO_OF_COLLISIONS = newT->MAX_NO_OF_COLLISIONS;
}

int HashMapHE::getTableSize() {
	return tableSize;
}

void HashMapHE::initialize(int tbSz) {
	table = new HashEntry*[tbSz];
	for (int i = 0; i < tbSz; i++) {
		table[i] = NULL;
	}
	tableSize = tbSz;
	LIMIT = tableSize * (1 - DENSITY_THRESHOLD);
	MAX_NO_OF_COLLISIONS = 0;
}

void HashMapHE::print() {
	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {
			cout << table[i]->getKey() << endl;
		}
		/*else {
			cout << "NULL" << endl;
		}*/
	}
}

bool HashMapHE::isEmpty() {
	return empty;
}
HashEntry ** HashMapHE::getTable() {
	return table;
}

HashMapHE::~HashMapHE() {
	for (int i = 0; i < tableSize; i++) {
			delete table[i];
	}
	delete[] table;
}