#include "HashMap.h"
#include "HashFunctions.h"

HashMap::HashMap(int tbSz) {
	if (tbSz == 0)
		tbSz = DEFAULT_TABLE_SIZE;
	initialize(tbSz);
}


HashEntry * HashMap::get(string key) {
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



void HashMap::put(string key, string dt) {
	size_t hashKey = hash<string>()(key);
	//unsigned int hashKey = HashFunctions::RSHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::JSHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::PJWHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::SDBMHash(key.c_str(), key.length());
	//unsigned int hashKey = HashFunctions::DJBHash(key.c_str(), key.length());

	int hash = hashKey % tableSize;
	if (table[hash] != NULL) {
		if (!table[hash]->getKey()._Equal(key)) {
			/*if it is a hashkey collission, the collisions is handled*/
			//cout << "key : " << key << " hashkey : " << hash << " Table[hash] =" << table[hash] << endl;
			handleCollision(table[hash], key, dt);
		}
		else {
			/*if theres no hashkey collision, we simply want to update the document list*/
			insertValueEntry(table[hash]->getValueEntry(), dt);
		}
	}
	else {
		ValueEntry * vt = new ValueEntry(dt, 0);
		table[hash] = new HashEntry(key, vt, 0);
		NO_OF_ENTRIES++;
	}

	/*TODO : If the number of entries have exceeded our density limit, we rehash.*/
	if ((tableSize - NO_OF_ENTRIES) <= DENSITY_THRESHOLD) {
		cout << "Rehashing ....... " << endl;
		reHashMap();		
	}
}

void HashMap::handleCollision(HashEntry * current, string key, string dt) {
	bool keyExist = false;
	int numberOfCol = 0;
	/*walk down the collision chain, compare, if value does not exist then create.*/
	while (current != NULL) {
		numberOfCol++;
		if (current->getKey()._Equal(key)) {
			/*Insert document to the document list*/
			insertValueEntry(current->getValueEntry(), dt);
			keyExist = true;
			break;
		}
		if (current->getNext() == NULL)
			break;

		current = current->getNext();
	}

	if (!keyExist) {
		ValueEntry * vt = new ValueEntry(dt, 0);
		current->setNext(new HashEntry(key, vt, 0));
		NO_OF_ENTRIES++;
	}
	if (numberOfCol >= MAX_NO_OF_COLLISIONS)
		MAX_NO_OF_COLLISIONS = numberOfCol;

	/*TODO : If HIGHEST_NO_OF_COLLISIONS is bigger than MAX_NO_OF_COLLISIONS, then expand hashtable and rehash everything*/
}

void HashMap::insertValueEntry(ValueEntry * initial, string dt) {
	ValueEntry * current = initial;
	bool documentExist = false;

	while (current != NULL) {

		if (current->getDocumentName()._Equal(dt)) {
			documentExist = true;
			break;
		}

		if (current->getNext() == NULL)
			break;

		current = current->getNext();
	}

	if (!documentExist) {
		/*create new document and insert it*/
		ValueEntry * vt = new ValueEntry(dt, 0);
		current->setNext(vt);
	}

}

void HashMap::InsertReHashValueEntries(string key, ValueEntry * initial, HashMap * newT) {
	ValueEntry * current = initial;
	while (current != NULL) {
		newT->put(key, current->getDocumentName());
		if (current->getNext() == NULL)
			break;
		current = current->getNext();
	}	
}

void HashMap::reHashMap() {

	/*Expanding the old table size by 2*/
	int newTableSize = 2 * tableSize;
	HashMap * newT = new HashMap(newTableSize);

	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {

			/*Inserting all value entries of the first node in the index*/
			InsertReHashValueEntries(table[i]->getKey(), table[i]->getValueEntry(), newT);

			/*Recursing and conituning in the list of collissions*/
			HashEntry * currentH = table[i]->getNext();
			while (currentH != NULL) {
				InsertReHashValueEntries(currentH->getKey(), currentH->getValueEntry(), newT);

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

	initialize(newTableSize);
	table = newT->getTable();
	MAX_NO_OF_COLLISIONS = newT->MAX_NO_OF_COLLISIONS;
}

int HashMap::getTableSize() {
	return tableSize;
}

void HashMap::initialize(int tbSz) {
	table = new HashEntry*[tbSz];
	for (int i = 0; i < tbSz; i++) {
		table[i] = NULL;
	}
	tableSize = tbSz;
	MAX_ENTRIES = tableSize * DENSITY_THRESHOLD;
	MAX_NO_OF_COLLISIONS = 0;
}

void HashMap::print() {
	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {
			cout << table[i]->getKey() << endl;
		}
		else {
			cout << "NULL" << endl;
		}
	}
}

HashEntry ** HashMap::getTable() {
	return table;
}
HashMap::~HashMap() {
	if (tableSize == 0)
		exit;

	for (int i = 0; i < tableSize; i++) {
		if (table[i] != NULL) {
			delete table[i];
		}
	}
	delete[] table;
}