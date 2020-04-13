#include <exception>

#include "StandardCardinalCipher.h"

void SCC::Encrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* encryptedBytes)
{
	if (*encryptedBytes != 0)
		throw std::exception("encryptedBytes should be initialized as zero");

	size_t blockCount = blockSize / KeySize;
	byte modulo = blockSize % KeySize;

	for (size_t i = 0; i < blockCount; i++)
	{
		for (size_t j = 0; j < KeySize; j++)
		{
			outArray[j + KeySize * i] = inArray[j + KeySize * i] ^ Key[j];

			(*encryptedBytes)++;
		}
	}

	for (byte i = 0; i < modulo; i++)
	{
		outArray[blockCount * KeySize + i] = inArray[blockCount * KeySize + i] ^ Key[i];

		(*encryptedBytes)++;
	}
}

void SCC::Decrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* decryptedBytes)
{
	if (*decryptedBytes != 0)
		throw std::exception("decryptedBytes should be initialized as zero");

	size_t blockCount = blockSize / KeySize;
	byte modulo = blockSize % KeySize;

	for (size_t i = 0; i < blockCount; i++)
	{
		for (size_t j = 0; j < KeySize; j++)
		{
			outArray[j + KeySize * i] = inArray[j + KeySize * i] ^ Key[j];

			(*decryptedBytes)++;
		}
	}

	for (byte i = 0; i < modulo; i++)
	{
		outArray[blockCount * KeySize + i] = inArray[blockCount * KeySize + i] ^ Key[i];

		(*decryptedBytes)++;
	}
}
