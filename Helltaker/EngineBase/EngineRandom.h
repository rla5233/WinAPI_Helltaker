#pragma once
#include <random>
#include <time.h>

// 설명 :
class UEngineRandom
{
public:
	static UEngineRandom MainRandom;

	// constrcuter destructer
	UEngineRandom();
	~UEngineRandom();

	// delete Function
	UEngineRandom(const UEngineRandom& _Other) = delete;
	UEngineRandom(UEngineRandom&& _Other) noexcept = delete;
	UEngineRandom& operator=(const UEngineRandom& _Other) = delete;
	UEngineRandom& operator=(UEngineRandom&& _Other) noexcept = delete;

	int RandomInt(int _Min, int _Max)
	{
		std::uniform_int_distribution<int> RandomCreate(_Min, _Max);
		return RandomCreate(MtGen);
	}

	float RandomFloat(float _Min, float _Max)
	{
		std::uniform_real_distribution<float> RandomCreate(_Min, _Max);
		return RandomCreate(MtGen);
	}

protected:

private:
	// 메르헨트위스터 난수 알고리즘을 사용합니다.
	// 일본의 어떤 수학교수님이 만든 알고리즘
	// 이걸 사용했다 => 시간에 의해서 언제나 난수입니다.
	// seed가 시간으로 계산된다.
	std::mt19937_64 MtGen = std::mt19937_64(time(nullptr));
};

