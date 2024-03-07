#pragma once

#include "Character.h"

// Ό³Έν :
class Sin_Judge : public Character
{
public:
	// constructor destructor
	Sin_Judge();
	~Sin_Judge();
	
	// delete Function
	Sin_Judge(const Sin_Judge& _Other) = delete;
	Sin_Judge(Sin_Judge&& _Other) noexcept = delete;
	Sin_Judge& operator=(const Sin_Judge& _Other) = delete;
	Sin_Judge& operator=(Sin_Judge&& _Other) noexcept = delete;

	void StateChange(ESinJudgeState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void Intro_AppearStart();
	void Intro_Appear(float _DeltaTime);
	void Intro_Appear1(float _DeltaTime);
	void Intro_Appear2(float _DeltaTime);


	void StateUpdate(float _DeltaTime);

private:
	int OrderCount = -1;

	ESinJudgeState State = ESinJudgeState::None;
};

