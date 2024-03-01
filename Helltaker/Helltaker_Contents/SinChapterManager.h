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

	void M_CreateSinBackGround();
	void M_CreateSinBG(std::string_view _Name);
	void M_CreateSinPit();
	void M_CreateSinGear();

	void M_CreateSinUnderPanel();
	void M_CreateSinPanel();
	void M_CreateSinPyre();

	void M_CreateSinShield();
	void M_CreateSinBridge();

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

	std::vector<SinComponent*> SinPyre;
	static const float SinFireInter;

	std::vector<SinComponent*> SinBridge;
	
	static bool IsLoad;
};

