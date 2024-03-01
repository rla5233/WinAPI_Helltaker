#pragma once

#include "RenderActor.h"

// ���� :
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

	void CreateImageRenderer(std::string_view _KeyName, SinRenderOrder _Order);
	UImageRenderer* GetImageRenderer(std::string_view _KeyName) const 
	{
		return ImageRenderers.find(_KeyName.data())->second;
	}

protected:


private:
	std::map<std::string, UImageRenderer*> ImageRenderers;

	FVector ReSetPos = FVector::Zero;
	bool IsMove = false;
};

