#pragma once

#include "Demon.h"

// Ό³Έν :
class Sin_Demon : public Demon
{
public:
	// constructor destructor
	Sin_Demon();
	~Sin_Demon();

	// delete Function
	Sin_Demon(const Sin_Demon& _Other) = delete;
	Sin_Demon(Sin_Demon&& _Other) noexcept = delete;
	Sin_Demon& operator=(const Sin_Demon& _Other) = delete;
	Sin_Demon& operator=(Sin_Demon&& _Other) noexcept = delete;

	static const FVector& GetIdleScale()
	{
		return Scale;
	}
	
	void SetDemon(std::string_view _Name, const FTransform& _FTransform) override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Sin_AppearStart() override;
	void Sin_Appear(float _DeltaTime) override;
	void CreateLandEffect();

	void VictoryStart() override;
	void CreateStarEffect();
	void CreateLovePlosion(float _DeltaTime);

private:
	std::list<UImageRenderer*> LandEffect;

	static const FVector Scale;
	static const FVector AppearScale;
	static const float AppearInter;

	static bool IsLoad;
};
