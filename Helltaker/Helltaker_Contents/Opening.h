#pragma once

#include <EngineCore/Level.h>

// Ό³Έν :
class Opening : public ULevel
{
public:
	// constructor destructor
	Opening();
	~Opening();

	// delete Function
	Opening(const Opening& _Other) = delete;
	Opening(Opening&& _Other) noexcept = delete;
	Opening& operator=(const Opening& _Other) = delete;
	Opening& operator=(Opening&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:
	std::list<AActor*> AllActors;

	float TimeCount = 0;
};
