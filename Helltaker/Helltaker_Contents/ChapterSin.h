#pragma once

#include "CutSceneManager.h"

// Ό³Έν :
class ChapterSin : public HellTakerManager
{
public:
	// constructor destructor
	ChapterSin();
	~ChapterSin();

	// delete Function
	ChapterSin(const ChapterSin& _Other) = delete;
	ChapterSin(ChapterSin&& _Other) noexcept = delete;
	ChapterSin& operator=(const ChapterSin& _Other) = delete;
	ChapterSin& operator=(ChapterSin&& _Other) noexcept = delete;

protected:

private:

};
