#pragma once
#include <Windows.h>
#include <string>

class CaesarCipher
{
public:
	CaesarCipher(byte shift);

	std::string Cipher(const std::string& text);
	std::string Decipher(const std::string& text);

private:
	CaesarCipher();

protected:
	byte Shift;
};