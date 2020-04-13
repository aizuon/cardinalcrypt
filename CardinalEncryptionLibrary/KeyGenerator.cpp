#include <random>
#include <exception>

#include "KeyGenerator.h"

KeyGenerator::KeyGenerator(byte keySize)
{
	KeySize = keySize;
}

byte* KeyGenerator::Generate()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, 0xFF);

	Key = new byte[KeySize];

	for (byte i = 0; i < KeySize; i++)
		Key[i] = dis(gen);

	return Key;
}
