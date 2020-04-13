#pragma once
#include <Windows.h>

class KeyGenerator
{
public:
	KeyGenerator(byte keySize);

	byte* Generate();

private:
	KeyGenerator();

	byte* Key;
	byte KeySize;
};