#include <exception>
#include <math.h>
#include <cctype>

#include "CaesarCipher.h"

CaesarCipher::CaesarCipher(byte shift)
{
	Shift = shift;

	if (Shift > 25)
		throw std::exception("Shift value cant be greater than 25");
}

std::string CaesarCipher::Cipher(const std::string& text)
{
	size_t length = text.length();

	std::string ciphered;
	ciphered.resize(length);
	
	for (size_t i = 0; i < length; i++)
	{
		if (isupper(text[i]))
		{
			ciphered[i] = char(int(text[i] + Shift - (int)'A') % 26 + (int)'A');
		}
		else
		{
			ciphered[i] = char(int(text[i] + Shift - (int)'a') % 26 + (int)'a');
		}
	}

	return ciphered;
}

std::string CaesarCipher::Decipher(const std::string& text)
{
	size_t length = text.length();

	std::string deciphered;
	deciphered.resize(length);

	for (size_t i = 0; i < length; i++)
	{
		if (isupper(text[i]))
		{
			deciphered[i] = char(int(text[i] + 26 - Shift - (int)'A') % 26 + (int)'A');
		}
		else
		{
			deciphered[i] = char(int(text[i] + 26 - Shift - (int)'a') % 26 + (int)'a');
		}
	}

	return deciphered;
}
