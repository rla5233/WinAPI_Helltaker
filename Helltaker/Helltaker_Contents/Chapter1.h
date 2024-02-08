#pragma once

#include "ChapterManager.h"

// ���� :
class Chapter1 : public ChapterManager
{
public:
	// constructor destructor
	Chapter1();
	~Chapter1();

	// delete Function
	Chapter1(const Chapter1& _Other) = delete;
	Chapter1(Chapter1&& _Other) noexcept = delete;
	Chapter1& operator=(const Chapter1& _Other) = delete;
	Chapter1& operator=(Chapter1&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;

private:

};