#pragma once

#include "ChapterManager.h"

// Ό³Έν :
class Chapter2 : public ChapterManager
{
public:
	// constructor destructor
	Chapter2();
	~Chapter2();
	
	// delete Function
	Chapter2(const Chapter2& _Other) = delete;
	Chapter2(Chapter2&& _Other) noexcept = delete;
	Chapter2& operator=(const Chapter2& _Other) = delete;
	Chapter2& operator=(Chapter2&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;

	void LevelStart(ULevel* _PrevLevel) override;

private:

};

