#pragma once
#include "CaesarCipher.h"

class ROT13 : public CaesarCipher
{
public:
	ROT13()
		: CaesarCipher(13)
	{ }
};