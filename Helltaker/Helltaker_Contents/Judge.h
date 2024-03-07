#pragma once

#include "Character.h"

// Ό³Έν :
class Judge : public Character
{
public:
	// constructor destructor
	Judge();
	~Judge();

	// delete Function
	Judge(const Judge& _Other) = delete;
	Judge(Judge&& _Other) noexcept = delete;
	Judge& operator=(const Judge& _Other) = delete;
	Judge& operator=(Judge&& _Other) noexcept = delete;

	void StateChange(ESinJudgeState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Intro_AppearStart();
	void Intro_Appear(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:



	ESinJudgeState State = ESinJudgeState::None;
	static bool IsLoad;
};
