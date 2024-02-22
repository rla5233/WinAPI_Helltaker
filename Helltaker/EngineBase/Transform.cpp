#include "Transform.h"
#include "EngineDebug.h"


bool (*FTransform::CollisionFunction[static_cast<int>(ECollisionType::Max)][static_cast<int>(ECollisionType::Max)])(const FTransform& _Left, const FTransform& _Right);

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CircleToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::Rect)] = FTransform::RectToRect;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::Rect)][static_cast<int>(ECollisionType::CirCle)] = FTransform::RectToCircle;
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::Rect)] = FTransform::CircleToRect;
	}
	~CollisionFunctionInit()
	{

	}
};

CollisionFunctionInit Inst;

bool FTransform::CircleToCircle(const FTransform& _Left, const FTransform& _Right)
{
	FVector Dir = _Left.Position - _Right.Position;
	float Len = _Left.Scale.hX() + _Right.Scale.hX();

	return Dir.Size2D() <= Len;
}

bool FTransform::CircleToRect(const FTransform& _Left, const FTransform& _Right)
{
	FTransform CirCleTransform = _Left;

	FTransform WRect = _Right; // 가로가 커진 Rect
	WRect.Scale.X += CirCleTransform.GetRadius() * 2.0f;
	FTransform HRect = _Right; // 세로가 커진 Rect
	HRect.Scale.Y += CirCleTransform.GetRadius() * 2.0f; // 세로가 커진 Rect

	if (true == PointToRect(_Left, WRect))
	{
		return true;
	}

	if (true == PointToRect(_Left, HRect))
	{
		return true;
	}

	FTransform LeftTopCirCleTransform;
	LeftTopCirCleTransform.SetPosition(_Right.LeftTop());
	LeftTopCirCleTransform.SetRadius(_Left.GetRadius());

	if (true == PointToCircle(_Left, LeftTopCirCleTransform))
	{
		return true;
	}

	FTransform RightTopCirCleTransform;
	RightTopCirCleTransform.SetPosition(_Right.RightTop());
	RightTopCirCleTransform.SetRadius(_Left.GetRadius());

	if (true == PointToCircle(_Left, RightTopCirCleTransform))
	{
		return true;
	}

	FTransform LeftBottomCirCleTransform;
	LeftBottomCirCleTransform.SetPosition(_Right.LeftBottom());
	LeftBottomCirCleTransform.SetRadius(_Left.GetRadius());

	if (true == PointToCircle(_Left, LeftBottomCirCleTransform))
	{
		return true;
	}

	FTransform RightBottomCirCleTransform;
	RightBottomCirCleTransform.SetPosition(_Right.RightBottom());
	RightBottomCirCleTransform.SetRadius(_Left.GetRadius());

	if (true == PointToCircle(_Left, RightBottomCirCleTransform))
	{
		return true;
	}

	return false;
}

bool FTransform::RectToCircle(const FTransform& _Left, const FTransform& _Right)
{
	return CircleToRect(_Right, _Left);
}

bool FTransform::RectToRect(const FTransform& _Left, const FTransform& _Right)
{
	if (_Left.Bottom() < _Right.Top())
	{
		return false;
	}

	if (_Left.Right() < _Right.Left())
	{
		return false;
	}

	if (_Right.Bottom() < _Left.Top())
	{
		return false;
	}

	if (_Right.Right() < _Left.Left())
	{
		return false;
	}


	return true;
}

bool FTransform::CircleToPoint(const FTransform& _Left, const FTransform& _Right)
{
	FVector Dir = _Left.Position - _Right.Position;
	float Len = _Left.Scale.hX();
	float Size = Dir.Size2D();

	return Size <= Len;
}

bool FTransform::PointToCircle(const FTransform& _Left, const FTransform& _Right)
{
	return CircleToPoint(_Right, _Left);
}
bool FTransform::PointToRect(const FTransform& _Left, const FTransform& _Right)
{
	return RectToPoint(_Right, _Left);
}

bool FTransform::RectToPoint(const FTransform& _Left, const FTransform& _Right)
{
	if (_Left.Bottom() < _Right.GetPosition().Y)
	{
		return false;
	}

	if (_Left.Right() < _Right.GetPosition().X)
	{
		return false;
	}

	if (_Right.GetPosition().Y < _Left.Top())
	{
		return false;
	}

	if (_Right.GetPosition().X < _Left.Left())
	{
		return false;
	}

	return  true;
}



FTransform::FTransform()
{
}

FTransform::~FTransform()
{
}

bool FTransform::Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("아직 충돌 함수를 만들지 않은 충돌입니다");
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](*this, _Other);
}
