#pragma once

#include "ContentsHelper.h"

#include <EngineCore/Level.h>

class SinComponent;

// Ό³Έν :
class SinChapterManager : public ULevel
{
public:
	// constructor destructor
	SinChapterManager();
	~SinChapterManager();
	
	// delete Function
	SinChapterManager(const SinChapterManager& _Other) = delete;
	SinChapterManager(SinChapterManager&& _Other) noexcept = delete;
	SinChapterManager& operator=(const SinChapterManager& _Other) = delete;
	SinChapterManager& operator=(SinChapterManager&& _Other) noexcept = delete;

	void M_CreateSinBG(std::string_view _Name);
	void M_CreateSinPit();
	void M_CreateSinGear();
	void M_CreateSinPanel();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;


private:
	std::map<__int64, AActor*> AllSMapActors;

	std::vector<SinComponent*> SinPit;
	static const float SinPitInterval;

	SinComponent* SinGear = nullptr;

	
	static bool IsLoad;
};

