#pragma once

#include "RenderActor.h"

// Ό³Έν :
class SinComponent : public RenderActor
{
public:
	// constructor destructor
	SinComponent();
	~SinComponent();
	
	// delete Function
	SinComponent(const SinComponent& _Other) = delete;
	SinComponent(SinComponent&& _Other) noexcept = delete;
	SinComponent& operator=(const SinComponent& _Other) = delete;
	SinComponent& operator=(SinComponent&& _Other) noexcept = delete;

	void MoveUp(float _Speed, float _DeltaTime);
	void MoveOn()
	{
		IsMove = true;
	}

	void MoveOff()
	{
		IsMove = false;
	}

	void SetResetPos(const FVector& _Pos)
	{
		ResetPos = _Pos;
	}

	void SetEndPos(const FVector& _Pos)
	{
		EndPos = _Pos;
	}

	void CreateImageRenderer(std::string_view _KeyName, SinRenderOrder _Order);
	UImageRenderer* GetImageRenderer(std::string_view _KeyName) const 
	{
		return ImageRenderers.find(_KeyName.data())->second;
	}

protected:


private:
	std::map<std::string, UImageRenderer*> ImageRenderers;

	FVector EndPos = FVector::Zero;
	FVector ResetPos = FVector::Zero;
	bool IsMove = false;
};

