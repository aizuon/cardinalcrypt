#pragma once
#include <Windows.h>
#include <string>

class Hash
{
public:
	virtual std::string DoHash(const byte* inArray, size_t blockSize) = 0;
};