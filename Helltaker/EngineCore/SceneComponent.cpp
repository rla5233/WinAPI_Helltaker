#include "SceneComponent.h"
#include "Actor.h"

USceneComponent::USceneComponent()
{
}

USceneComponent::~USceneComponent()
{
}

FTransform USceneComponent::GetActorBaseTransform()
{
	FTransform Trans = Transform;
	Trans.AddPosition(GetOwner()->GetActorLocation());
	return Trans;
}
