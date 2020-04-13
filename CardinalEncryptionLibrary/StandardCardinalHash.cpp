#include <sstream>
#include <iomanip>
#include <algorithm>

#include "StandardCardinalHash.h"

std::string SCH::DoHash(const byte* inArray, size_t blockSize)
{
	size_t times = blockSize / HashSize;
	size_t modulo = blockSize % HashSize;

	byte output[HashSize];
	memcpy(output, Init, HashSize);

	for (size_t i = 0; i < times; i++)
	{
		for (size_t j = 0; j < HashSize; j++)
		{
			output[j] = output[j] ^ inArray[i * HashSize + j];
		}
	}

	for (size_t i = 0; i < modulo; i++)
	{
		for (size_t j = 0; j < HashSize; j++)
		{
			output[j] = output[j] ^ inArray[times * HashSize + i];
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
