#pragma once
#include <Windows.h>
#include <string>

class ACH
{
public:
	static std::string DoHash(const byte* inArray, size_t blockSize);

private:
	const static size_t HashSize = 32;
	static constexpr uint32_t Init[HashSize / sizeof(uint32_t)] =
	{
		0x14442C27, 0x560CC8DE,
		0x427210E0, 0x23C9688F,
		0x739D1F14, 0x316A25C3,
		0x636095D7, 0x955D3591,
	};
	const static size_t MagicSize = 4;
	static constexpr byte Magic[MagicSize] = { 0x19, 0x44, 0x53, 0x85 };
};