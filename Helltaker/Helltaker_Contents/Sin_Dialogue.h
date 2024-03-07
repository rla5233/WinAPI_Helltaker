#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Sin_Dialogue : public RenderActor
{
public:
	// constructor destructor
	Sin_Dialogue();
	~Sin_Dialogue();

	// delete Function
	Sin_Dialogue(const Sin_Dialogue& _Other) = delete;
	Sin_Dialogue(Sin_Dialogue&& _Other) noexcept = delete;
	Sin_Dialogue& operator=(const Sin_Dialogue& _Other) = delete;
	Sin_Dialogue& operator=(Sin_Dialogue&& _Other) noexcept = delete;

	void StateChange(ESinDialogueState _State);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);
	
	void SetHell();
	void SetSin();

	void MoveStart();
	void Move(float _DeltaTime);
	
	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* Down_ImageRenderer = nullptr;
	UImageRenderer* Up_ImageRenderer = nullptr;
	static const FVector DownSinScale;
	static const FVector UpSinScale;

	UImageRenderer* DarkHell_Renderer = nullptr;
	UImageRenderer* LitHell_Renderer = nullptr;
	static const FVector HellScale;

	ESinDialogueState State = ESinDialogueState::None;
	static bool IsLoad;
};
