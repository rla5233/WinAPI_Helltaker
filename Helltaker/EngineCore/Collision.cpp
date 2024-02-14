#include "Collision.h"
#include <map>
#include <list>
#include "Level.h"
#include "Actor.h"

UCollision::UCollision()
{}

UCollision::~UCollision()
{}

void UCollision::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UCollision*>>& Collisions = Level->Collisions;
	// 나의 오더가 바뀌기전에 혹시나 내가 어떤 그룹에 속해있다면
	// 그 그룹에서 빠져 나온다.
	Collisions[GetOrder()].remove(this);

	// 나의 오더가 바뀐다.
	UTickObject::SetOrder(_Order);

	Collisions[GetOrder()].push_back(this);
}

void UCollision::BeginPlay()
{
	USceneComponent::BeginPlay();
}

// true 충돌한 객체가 있다.
bool UCollision::CollisionCheck(int _Order, std::vector<UCollision*>& _Result)
{
	// 나랑 특정개수의 콜리전이랑 충돌해야 한다.
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::list<UCollision*>& Collisions = Level->Collisions[_Order];

	FTransform ThisTransform = GetActorBaseTransform();

	for (UCollision* _OtherCollision : Collisions)
	{
		FTransform OtherTransform = _OtherCollision->GetActorBaseTransform();

		if (true == ThisTransform.Collision(ColType, _OtherCollision->ColType, OtherTransform))
		{
			_Result.push_back(_OtherCollision);
		}
	}

	return false == _Result.empty();
}