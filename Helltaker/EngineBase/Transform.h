#pragma once
#include "EngineMath.h"

// Ό³Έν :
class FTransform
{
public:
	// constrcuter destructer
	FTransform();
	FTransform(const FVector& _Pos, const FVector& _Scale)
		: Position(_Pos), Scale(_Scale)
	{

	}
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
	FVector GetScale() const
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
	FVector GetPosition() const
	{
		return Position;
	}

	float Left() const
	{
		return Position.X - Scale.hX();
	}
	float Top() const
	{
		return Position.Y - Scale.hY();
	}
	float Right() const
	{
		return Position.X + Scale.hX();
	}
	float Bottom() const
	{
		return Position.Y + Scale.hY();
	}

	int iLeft() const
	{
		return std::lround(Left());
	}
	int iRight() const
	{
		return std::lround(Right());
	}
	int iTop() const
	{
		return std::lround(Top());
	}
	int iBottom() const
	{
		return std::lround(Bottom());
	}

protected:

private:
	FVector Scale;
	FVector Position;
};

