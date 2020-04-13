#include <iostream>
#include <chrono>
#include <functional>

#include "../CardinalEncryptionLibrary/StandardCardinalCipher.h"
#include "../CardinalEncryptionLibrary/AdvancedCardinalCipher.h"
#include "../CardinalEncryptionLibrary/Base64.h"
#include "../CardinalEncryptionLibrary/CaesarCipher.h"
#include "../CardinalEncryptionLibrary/ROT13.h"
#include "../CardinalEncryptionLibrary/StandardCardinalHash.h"
#include "../CardinalEncryptionLibrary/AdvancedCardinalHash.h"

class ScopeTimer
{
public:
	ScopeTimer(const std::string& methodName, size_t loopCount)
	{
		m_MethodName = methodName;
		m_LoopCount = loopCount;

		m_Start = std::chrono::high_resolution_clock::now();
	}

	~ScopeTimer()
	{
		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> duration = end - m_Start;
		float ms = duration.count() * 1000.0f;

		std::cout << m_LoopCount << " loops of " << m_MethodName << " took " << ms << "ms\n";
	}

private:
	std::chrono::time_point<std::chrono::steady_clock> m_Start;

	std::string m_MethodName;
	size_t m_LoopCount;
};

class LambdaTimer
{
public:
	LambdaTimer(const std::string& methodName, size_t loopCount, const std::function<void()>& f)
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (size_t i = 0; i < loopCount; i++)
			f();

		auto end = std::chrono::high_resolution_clock::now();

		std::chrono::duration<float> duration = end - start;
		float ms = duration.count() * 1000.0f;

		std::cout << loopCount << " loops of " << methodName << " took " << ms << "ms\n";
	}
};

int main()
{
	SCC standard(16);
	byte sccinarray[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	byte sccoutarray[17];
	size_t sccencryptedbytes = 0;
	standard.Encrypt(sccinarray, 17, sccoutarray, &sccencryptedbytes);
	for (size_t i = 0; i < sccencryptedbytes; i++)
		std::cout << (int)sccoutarray[i] << " ";
	std::cout << "\n";

	byte sccoutarray2[17];
	size_t sccdecryptedbytes = 0;
	standard.Decrypt(sccoutarray, 17, sccoutarray2, &sccdecryptedbytes);
	for (size_t i = 0; i < sccdecryptedbytes; i++)
		std::cout << (int)sccoutarray2[i] << " ";
	std::cout << "\n";

	ACC advanced(16);
	byte accinarray[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	byte accoutarray[17];
	size_t accencryptedbytes = 0;
	advanced.Encrypt(accinarray, 17, accoutarray, &accencryptedbytes);
	for (size_t i = 0; i < accencryptedbytes; i++)
		std::cout << (int)accoutarray[i] << " ";
	std::cout << "\n";

	byte accoutarray2[17];
	size_t accdecryptedbytes = 0;
	advanced.Decrypt(accoutarray, 17, accoutarray2, &accdecryptedbytes);
	for (size_t i = 0; i < accdecryptedbytes; i++)
		std::cout << (int)accoutarray2[i] << " ";
	std::cout << "\n";

	std::cout << Base64::Cipher("test") << "\n";

	//std::cout << Base64::Decipher("dGVzdA==") << "\n"; //broken

	CaesarCipher caesercipher(3);
	std::cout << caesercipher.Cipher("test") << "\n";
	std::cout << caesercipher.Decipher("whvw") << "\n";

	ROT13 rot13;
	std::cout << rot13.Cipher("test") << "\n";
	std::cout << rot13.Decipher("grfg") << "\n";

	byte scharray[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	std::cout << SCH::DoHash(scharray, 17) << "\n";

	byte acharray[17] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };
	std::cout << ACH::DoHash(acharray, 17) << "\n";

#pragma region Performance

	ACC advanced_perf(32);
	byte accinarray_perf[1024];

	auto l = [&advanced_perf, accinarray_perf]()
	{
		byte accoutarray_perf[1024];
		size_t accencryptedbytes_perf = 0;
		advanced_perf.Encrypt(accinarray_perf, 1024, accoutarray_perf, &accencryptedbytes_perf);

		byte accoutarray2_perf[1024];
		size_t accdecryptedbytes_perf = 0;
		advanced_perf.Decrypt(accoutarray_perf, 1024, accoutarray2_perf, &accdecryptedbytes_perf);
	};

	LambdaTimer timer("ACC", 1000, l);
	
	byte acharray_perf[1024];

	auto l2 = [acharray_perf]()
	{
		std::string hash = ACH::DoHash(acharray_perf, 1024);
	};

	LambdaTimer timer2("ACH", 1000, l2);

	byte* acharray_perf2 = new byte[1024 * 500 * 1000]; //500MB

	auto l3 = [acharray_perf2]()
	{
		std::string hash = ACH::DoHash(acharray_perf2, 1024 * 500 * 1000);
	};

	LambdaTimer timer3("500MB ACH", 1, l3);

	delete[] acharray_perf2;

#pragma endregion

	std::cin.get();

	return 0;
}