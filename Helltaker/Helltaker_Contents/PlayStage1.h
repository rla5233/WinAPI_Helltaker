#pragma once
#include "StageManager.h"

class UPlayStage1 : public StageManager
{
public:
	// constructor destructor
	UPlayStage1();
	~UPlayStage1();

	// delete Function
	UPlayStage1(const UPlayStage1& _Other) = delete;
	UPlayStage1(UPlayStage1&& _Other) noexcept = delete;
	UPlayStage1& operator=(const UPlayStage1& _Other) = delete;
	UPlayStage1& operator=(UPlayStage1&& _Other) noexcept = delete;

protected:
	virtual void BeginPlay() override;

private:

};
