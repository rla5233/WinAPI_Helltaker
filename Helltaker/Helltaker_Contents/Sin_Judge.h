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
	void Intro_Appear3(float _DeltaTime);
	void Intro_Appear4(float _DeltaTime);
	void Intro_Appear5(float _DeltaTime);
	void Intro_Appear6(float _DeltaTime);
	void CreateBigChain();
	void BigChainFadeAppear(float _DeltaTime);
	void BigChainFadeOutUpdate(float _DeltaTime);
	void BigChainFadeInUpdate(float _DeltaTime);

	void Chap3_ChainStart();
	void Chap3_Chain(float _DeltaTime);
	void ChainFadeAppear(float _DeltaTime);
	void ChainFadeOutUpdate(float _DeltaTime);
	void ChainFadeInUpdate(float _DeltaTime);

	void Chap3_BindStart();
	void Chap3_Bind(float _DeltaTime);
	void Chap3_Bind1(float _DeltaTime);
	void Chap3_Bind2(float _DeltaTime);
	void Chap3_Bind3(float _DeltaTime);
	void Chap3_Bind4(float _DeltaTime);
	void Chap3_Bind5(float _DeltaTime);

	void ChainRendererRemove();
	void ArmRendererRemove();
	void SingleChainSound();
	void DoubleChainSound();
	void RandChainASound();
	void RandChainBSound();

	void Chap3_FlyStart();
	void Chap3_Fly(float _DeltaTime);
	void Chap3_Fly1();
	void Chap3_Fly2(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	std::list<UImageRenderer*> BigChainRenderer;
	std::list<UImageRenderer*> ChainRenderer;
	UImageRenderer* ArmRenderer = nullptr;
	static const float FadeOutDelayTime;
	float TimeCount = 0.0f;

	static const float IntroDelayTime;

	static const float BindDelayTime;
	bool BindASoundPlay = false;
	bool BindBSoundPlay = false;

	UImageRenderer* S_PentaRenderer = nullptr;
	UImageRenderer* B_PentaRenderer = nullptr;
	FVector S_PentaTargetScale = FVector::Zero;
	FVector B_PentaTargetScale = FVector::Zero;

	int OrderCount = -1;

	ESinJudgeState State = ESinJudgeState::None;
};

