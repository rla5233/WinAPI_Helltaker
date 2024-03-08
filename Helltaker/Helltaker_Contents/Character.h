#pragma once

#include "RenderActor.h"

// Ό³Έν :
class Character : public RenderActor
{
public:
	// constructor destructor
	Character();
	~Character();

	// delete Function
	Character(const Character& _Other) = delete;
	Character(Character&& _Other) noexcept = delete;
	Character& operator=(const Character& _Other) = delete;
	Character& operator=(Character&& _Other) noexcept = delete;

	template<typename EnumType>
	void CreateImageRenderer(EnumType _Order)
	{
		ImageRenderer = AActor::CreateImageRenderer(_Order);
	}

	template<typename EnumType>
	void CreateNameRenderer(EnumType _Order)
	{
		NameRenderer = AActor::CreateImageRenderer(_Order);
	}

	void SetImageRendererMove();

	UImageRenderer* GetImageRenderer() const
	{
		return ImageRenderer;
	}

	UImageRenderer* GetNameRenderer() const
	{
		return NameRenderer;
	}

	void SetState(ECharacterState _State)
	{
		State = _State;
	}
	
	void StateChange(ECharacterState _State);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float _DeltaTime) override;

private:
	void IdleStart();
	void Idle(float _DeltaTime);

	void AppearStart();
	void Appear(float _DeltaTime);

	void StateUpdate(float _DeltaTime);

private:
	UImageRenderer* ImageRenderer = nullptr;
	UImageRenderer* NameRenderer = nullptr;

	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;

	ECharacterState State = ECharacterState::None;
	static bool IsLoad;
};
