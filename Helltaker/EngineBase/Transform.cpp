#include "Transform.h"
#include "EngineDebug.h"


bool (*FTransform::CollisionFunction[static_cast<int>(Rect)][static_cast<int>(Rect)])(const FTransform& _Left, const FTransform& _Right);

class CollisionFunctionInit
{
public:
	CollisionFunctionInit()
	{
		FTransform::CollisionFunction[static_cast<int>(ECollisionType::CirCle)][static_cast<int>(ECollisionType::CirCle)] = FTransform::CircleToCircle;
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



FTransform::FTransform()
{}

FTransform::~FTransform()
{}

bool FTransform::Collision(ECollisionType _ThisType, ECollisionType _OtherType, const FTransform& _Other)
{
	if (nullptr == CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)])
	{
		MsgBoxAssert("아직 충돌 함수를 만들지 않은 충돌입니다");
	}

	return CollisionFunction[static_cast<int>(_ThisType)][static_cast<int>(_OtherType)](*this, _Other);
}
