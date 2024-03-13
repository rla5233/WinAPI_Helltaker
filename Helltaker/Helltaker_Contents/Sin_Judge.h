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
	void Intro_Appear();
	void Intro_Appear1();
	void Intro_Appear2();

	void Chap3_ChainStart();
	void Chap3_Chain(float _DeltaTime);
	void ChainFadeAppear(float _DeltaTime);
	void ChainFadeOutUpdate(float _DeltaTime);
	void ChainFadeInUpdate(float _DeltaTime);

	void Chap3_BindStart();
	void Chap3_Bind();

	void ChainRendererRemove();
	void ArmRendererRemove();

	void Chap3_FlyStart();
	void Chap3_Fly();
	void Chap3_Fly1();

	void StateUpdate(float _DeltaTime);

private:
	std::list<UImageRenderer*> ChainRenderer;
	UImageRenderer* ArmRenderer = nullptr;
	static const float FadeOutDelayTime;
	float TimeCount = 0.0f;

	UImageRenderer* PentaRenderer = nullptr;

	int OrderCount = -1;

	ESinJudgeState State = ESinJudgeState::None;
};

