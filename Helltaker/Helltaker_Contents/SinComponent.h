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

	void SetResetPosY(float _PosY)
	{
		ResetPosY = _PosY;
	}

	void SetEndPosY(float _PosY)
	{
		EndPosY = _PosY;
	}

	void CreateImageRenderer(std::string_view _KeyName, SinRenderOrder _Order);
	UImageRenderer* GetImageRenderer(std::string_view _KeyName) const 
	{
		return ImageRenderers.find(_KeyName.data())->second;
	}

protected:


private:
	std::map<std::string, UImageRenderer*> ImageRenderers;
	


	float EndPosY = 0.0f;
	float ResetPosY = 0.0f;
	bool IsMove = false;
};

