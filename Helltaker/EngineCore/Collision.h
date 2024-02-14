#pragma once
#include "SceneComponent.h"
#include <vector>

// Ό³Έν :
class UCollision : public USceneComponent
{
public:
	// constrcuter destructer
	UCollision();
	~UCollision();

	// delete Function
	UCollision(const UCollision& _Other) = delete;
	UCollision(UCollision&& _Other) noexcept = delete;
	UCollision& operator=(const UCollision& _Other) = delete;
	UCollision& operator=(UCollision&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;

	template<typename EnumType>
	bool CollisionCheck(EnumType _Order, std::vector<UCollision*>& _Result)
	{
		return CollisionCheck(static_cast<int>(_Order), _Result);
	}

	bool CollisionCheck(int _Order, std::vector<UCollision*>& _Result);

protected:
	void BeginPlay() override;

private:
	ECollisionType ColType = ECollisionType::CirCle;
};

