#pragma once
#include <Windows.h>

#include "BaseCipher.h"

class ACC : public Cipher
{
public:
	ACC(byte keySize)
		: Cipher(keySize)
	{ }

	void Encrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* encryptedBytes) override;
	void Decrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* decryptedBytes) override;

private:
	ACC();
};