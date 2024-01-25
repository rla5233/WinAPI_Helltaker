#pragma once
#include "EngineMath.h"

// Ό³Έν :
class FTransform
{
public:
	// constrcuter destructer
	FTransform();
	~FTransform();

	// delete Function
	//FTransform(const FTransform& _Other) = delete;
	//FTransform(FTransform&& _Other) noexcept = delete;
	//FTransform& operator=(const FTransform& _Other) = delete;
	//FTransform& operator=(FTransform&& _Other) noexcept = delete;

public:
	void SetScale(FVector _Value)
	{
		Scale = _Value;
	}
	FVector GetScale()
	{
		return Scale;
	}
	void SetPosition(FVector _Value)
	{
		Position = _Value;
	}
	void AddPosition(FVector _Value)
	{
		Position += _Value;
	}
	FVector GetPosition()
	{
		return Position;
	}

	float Left()
	{
		return Position.X - Scale.hX();
	}
	float Right()
	{
		return Position.X + Scale.hX();
	}
	float Top()
	{
		return Position.Y - Scale.hY();
	}
	float Bottom()
	{
		return Position.Y + Scale.hY();
	}

	int iLeft()
	{
		return static_cast<int>(Left());
	}
	int iRight()
	{
		return static_cast<int>(Right());
	}
	int iTop()
	{
		return static_cast<int>(Top());
	}
	int iBottom()
	{
		return static_cast<int>(Bottom());
	}

protected:

private:
	FVector Scale;
	FVector Position;
};

