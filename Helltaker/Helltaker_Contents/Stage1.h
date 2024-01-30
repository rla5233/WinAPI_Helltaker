#pragma once
#include "StageManager.h"

class Stage1 : public StageManager
{
public:
	// constructor destructor
	Stage1();
	~Stage1();

	// delete Function
	Stage1(const Stage1& _Other) = delete;
	Stage1(Stage1&& _Other) noexcept = delete;
	Stage1& operator=(const Stage1& _Other) = delete;
	Stage1& operator=(Stage1&& _Other) noexcept = delete;

protected:

private:

};
