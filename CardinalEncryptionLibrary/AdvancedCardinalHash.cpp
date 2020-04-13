#include <sstream>
#include <iomanip>
#include <algorithm>

#include "AdvancedCardinalHash.h"

std::string ACH::DoHash(const byte* inArray, size_t blockSize)
{
	size_t times = blockSize / HashSize;
	size_t modulo = blockSize % HashSize;

	uint32_t Magic_or[MagicSize];
	memcpy(Magic_or, Magic, MagicSize);

	for (size_t i = 0; i < blockSize; i++)
	{
		for (size_t j = 0; j < MagicSize; j++)
		{
			Magic_or[j] = Magic_or[j] | inArray[i];
		}
	}

	byte output[HashSize];
	memcpy(output, Init, HashSize);

	for (size_t i = 0; i < times; i++)
	{
		for (size_t j = 0; j < HashSize; j++)
		{
			output[j] = output[j] ^ inArray[i * HashSize + j];
			output[j] = output[j] * Magic_or[(i * HashSize + j) % MagicSize];
		}
	}

	for (size_t i = 0; i < modulo; i++)
	{
		for (size_t j = 0; j < HashSize; j++)
		{
			output[j] = output[j] ^ inArray[times * HashSize + i];
			output[j] = output[j] * Magic_or[(times * HashSize + i) % MagicSize];
		}
	}

	std::stringstream ss;
	ss << std::hex;
	for (size_t i = 0; i < HashSize; i++)
	{
		ss << std::setw(2) << std::setfill('0') << (int)output[i];
	}
	std::string outputString = ss.str();
	std::transform(outputString.begin(), outputString.end(), outputString.begin(), std::tolower);

	return outputString;
}
