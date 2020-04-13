#include <string>
#include <cstdint>
#include <exception>

#include "Base64.h"

std::string Base64::Cipher(const std::string& text)
{
	size_t length = text.length();

	size_t modulo = length % 3;

	size_t cipheredlength = ((length / 3) + (modulo > 0)) * 4;
	std::string ciphered;
	ciphered.resize(cipheredlength);

	uint32_t temp;

	for (size_t i = 0; i < length / 3; i++)
	{
		temp = text[3 * i] << 16;
		temp += text[3 * i + 1] << 8;
		temp += text[3 * i + 2];
		ciphered[4 * i] = s_EncodingTable[(temp & 0x00FC0000) >> 18];
		ciphered[4 * i + 1] = s_EncodingTable[(temp & 0x0003F000) >> 12];
		ciphered[4 * i + 2] = s_EncodingTable[(temp & 0x00000FC0) >> 6];
		ciphered[4 * i + 3] = s_EncodingTable[(temp & 0x0000003F)];
	}

	switch (modulo)
	{
		case 1:
			temp = text[length - 1] << 16;
			ciphered[cipheredlength - 4] = s_EncodingTable[(temp & 0x00FC0000) >> 18];
			ciphered[cipheredlength - 3] = s_EncodingTable[(temp & 0x0003F000) >> 12];
			ciphered[cipheredlength - 2] = '=';
			ciphered[cipheredlength - 1] = '=';
			break;

		case 2:
			temp = text[length - 2] << 16;
			temp += text[length - 1] << 8;
			ciphered[cipheredlength - 4] = s_EncodingTable[(temp & 0x00FC0000) >> 18];
			ciphered[cipheredlength - 3] = s_EncodingTable[(temp & 0x0003F000) >> 12];
			ciphered[cipheredlength - 2] = s_EncodingTable[(temp & 0x00000FC0) >> 6];
			ciphered[cipheredlength - 1] = '=';
			break;
	}

	return ciphered;
}

std::string Base64::Decipher(const std::string& text)
{
	size_t length = text.length();

	if (length % 4)
		throw std::exception("Invalid Base64 length");

	size_t padding = 0;

	if (text[length - 1] == '=')
		padding++;
	if (text[length - 2] == '=') 
		padding++;

	size_t decipheredlength = ((length / 4) * 3) - padding;
	std::string deciphered;
	deciphered.resize(decipheredlength);

	uint32_t temp = 0;

	for (size_t i = 0; i < length; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			temp <<= 6;
			if (text[i] >= 'A' && text[i] <= 'Z')
				temp |= text[i] - 'A';
			else if (text[i] >= 'a' && text[i] <= 'z')
				temp |= text[i] - 'G';
			else if (text[i] >= '0' && text[i] <= '9')
				temp |= text[i] + 0x04;
			else if (text[i] == '+')
				temp |= '>';
			else if (text[i] == '/')
				temp |= '?';
			else if (text[i] == '=')
			{
				switch (length - i)
				{
					case 1:
						deciphered[decipheredlength - 2] = (temp >> 16) & 0x000000FF;
						deciphered[decipheredlength - 1] = (temp >> 8) & 0x000000FF;
						return deciphered;

					case 2:
						deciphered[decipheredlength - 1] = (temp >> 10) & 0x000000FF;
						return deciphered;

					default:
						throw std::exception("Invalid padding in Base64");
				}
			}
			else
				throw std::exception("Invalid character in Base64");
		}

		deciphered[3 * i] = (temp >> 16) & 0x000000FF;
		deciphered[3 * i + 1] = (temp >> 8) & 0x000000FF;
		deciphered[3 * i + 2] = temp & 0x000000FF;
	}

	return deciphered;
}
