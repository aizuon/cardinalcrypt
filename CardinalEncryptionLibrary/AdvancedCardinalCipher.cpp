#include <exception>

#include "AdvancedCardinalCipher.h"

void ACC::Encrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* encryptedBytes)
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

		byte* rowtemp = new byte[KeySize];

		memcpy(rowtemp, outArray + (i * KeySize), KeySize);

		for (int n = 0; n < Dimension; n++)
		{
			for (int m = 0; m < Dimension - 1; m++)
			{
				outArray[n + (m * Dimension) + (i * KeySize)] = rowtemp[n + ((m + 1) * Dimension)];
			}
		}

		for (int m = 0; m < Dimension; m++)
		{
			outArray[m + ((Dimension - 1) * Dimension) + (i * KeySize)] = rowtemp[m];
		}

		delete[] rowtemp;

		byte* columntemp = new byte[KeySize];

		memcpy(columntemp, outArray + (i * KeySize), KeySize);

		for (int n = 0; n < Dimension; n++)
		{
			for (int m = 0; m < Dimension - 1; m++)
			{
				outArray[(n * Dimension) + m + (i * KeySize)] = columntemp[(n * Dimension) + (m + 1)];
			}
		}

		for (int m = 0; m < Dimension; m++)
		{
			outArray[(Dimension * (m + 1)) - 1 + (i * KeySize)] = columntemp[(Dimension * m)];
		}

		delete[] columntemp;
	}

	for (byte i = 0; i < modulo; i++)
	{
		outArray[blockCount * KeySize + i] = inArray[blockCount * KeySize + i] ^ Key[i];

		(*encryptedBytes)++;
	}
}

void ACC::Decrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* decryptedBytes)
{
	if (*decryptedBytes != 0)
		throw std::exception("decryptedBytes should be initialized as zero");

	size_t blockCount = blockSize / KeySize;
	byte modulo = blockSize % KeySize;

	for (size_t i = 0; i < blockCount; i++)
	{
		byte* columntemp = new byte[KeySize];

		memcpy(columntemp, inArray + (i * KeySize), KeySize);

		for (int n = 0; n < Dimension; n++)
		{
			for (int m = 1; m < Dimension; m++)
			{
				outArray[(n * Dimension) + m + (i * KeySize)] = columntemp[(n * Dimension) + (m - 1)];
			}
		}

		for (int m = 0; m < Dimension; m++)
		{
			outArray[(Dimension * m) + (i * KeySize)] = columntemp[(Dimension * (m + 1)) - 1];
		}

		delete[] columntemp;

		byte* rowtemp = new byte[KeySize];

		memcpy(rowtemp, outArray + (i * KeySize), KeySize);

		for (int n = 0; n < Dimension; n++)
		{
			for (int m = 1; m < Dimension; m++)
			{
				outArray[n + (m * Dimension) + (i * KeySize)] = rowtemp[n + ((m - 1) * Dimension)];
			}
		}

		for (int m = 0; m < Dimension; m++)
		{
			outArray[m + (i * KeySize)] = rowtemp[m + ((Dimension - 1) * Dimension)];
		}

		delete[] rowtemp;

		for (size_t j = 0; j < KeySize; j++)
		{
			outArray[j + KeySize * i] = outArray[j + KeySize * i] ^ Key[j];

			(*decryptedBytes)++;
		}
	}

	for (byte i = 0; i < modulo; i++)
	{
		outArray[blockCount * KeySize + i] = inArray[blockCount * KeySize + i] ^ Key[i];

		(*decryptedBytes)++;
	}
}
