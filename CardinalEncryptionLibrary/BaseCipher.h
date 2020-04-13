#pragma once
#include <Windows.h>

class Cipher
{
public:
	Cipher(byte keySize);
	~Cipher();

	virtual void Encrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* encryptedBytes) = 0;
	virtual void Decrypt(const byte* inArray, size_t blockSize, byte* outArray, size_t* decryptedBytes) = 0;

private:
	Cipher();

protected:
	byte* Key;
	byte KeySize;

	byte Dimension;
};