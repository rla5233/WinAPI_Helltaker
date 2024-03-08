#pragma once

#include "SinChapterManager.h"

// Ό³Έν :
class SinChapter1 : public SinChapterManager
{
public:
	// constructor destructor
	SinChapter1();
	~SinChapter1();
	
	// delete Function
	SinChapter1(const SinChapter1& _Other) = delete;
	SinChapter1(SinChapter1&& _Other) noexcept = delete;
	SinChapter1& operator=(const SinChapter1& _Other) = delete;
	SinChapter1& operator=(SinChapter1&& _Other) noexcept = delete;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime);

	virtual void LevelStart(ULevel* _PrevLevel) override;
	virtual void LevelEnd(ULevel* _NextLevel) override;

	void Phase1_Start() override;
	void Phase2_Start() override;

private:


	static bool IsLoad;
};

