#pragma once

#include "RenderActor.h"

// ���� :
class SinMoveActor : public RenderActor
{
public:
	// constructor destructor
	SinMoveActor();
	~SinMoveActor();

	// delete Function
	SinMoveActor(const SinMoveActor& _Other) = delete;
	SinMoveActor(SinMoveActor&& _Other) noexcept = delete;
	SinMoveActor& operator=(const SinMoveActor& _Other) = delete;
	SinMoveActor& operator=(SinMoveActor&& _Other) noexcept = delete;

	void MoveOn()
	{
		IsMove = true;
	}

	void MoveOff()
	{
		IsMove = false;
	}

	bool IsMoveOn() const
	{
		return IsMove;
	}

	float GetResetPosY() const
	{
		return ResetPosY;
	}

	void SetResetPosY(float _PosY)
	{
		ResetPosY = _PosY;
	}

	float GetEndPosY() const
	{
		return EndPosY;
	}

	void SetEndPosY(float _PosY)
	{
		EndPosY = _PosY;
	}

	void LerfMoveOn()
	{
		IsLerfMove = true;
	}

	bool IsLerfMoveOn() const
	{
		return IsLerfMove;
	}

	void SetLerfStartPos(const FVector& _Pos)
	{
		StartPos = _Pos;
	}

	void SetLerfTargetPos(const FVector& _Pos)
	{
		TargetPos = _Pos;
	}

	void MoveLerfUpdate(float _DeltaTime, float _TimeWeight);

	void MoveY_Update(float _Speed, float _DeltaTime);
protected:

private:
	FVector StartPos = FVector::Zero;
	FVector TargetPos = FVector::Zero;
	float LerfMoveTime = 0.0f;
	bool IsLerfMove = false;

	float EndPosY = 0.0f;
	float ResetPosY = 0.0f;
	bool IsMove = false;
};
