#include <exception>
#include <math.h>

#include "BaseCipher.h"
#include "KeyGenerator.h"

Cipher::Cipher(byte keySize)
{
	KeySize = keySize;

	if (KeySize % 4 != 0)
		throw std::exception("keySize must be a square number");

	Dimension = sqrt(KeySize);

	KeyGenerator Generator(KeySize);
	Key = Generator.Generate();
}

Cipher::~Cipher()
{
	delete[] Key;
}
