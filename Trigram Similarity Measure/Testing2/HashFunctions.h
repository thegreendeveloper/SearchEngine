#pragma once
class HashFunctions
{
public:
	static unsigned int RSHash(const char* str, unsigned int length);
	static unsigned int JSHash(const char* str, unsigned int length);
	static unsigned int PJWHash(const char* str, unsigned int length);
	static unsigned int SDBMHash(const char* str, unsigned int length);
	static unsigned int DJBHash(const char* str, unsigned int length);
};

