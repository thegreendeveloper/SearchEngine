#pragma once
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>
#include <sstream>

#include "HashEntry.h"
#include "HashMapHE.h"


using namespace std;

class Utilities
{
public:
	static bool ImportFile(string fileName, HashMapHE * map);
	static int getLineCount(string fileName);
};

