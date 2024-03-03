#include "Chain.h"

#include <EngineCore/EngineResourcesManager.h>

bool Chain::IsLoad = false;

Chain::Chain()
{
}

Chain::~Chain()
{
}

void Chain::BeginPlay()
{
	if (false == IsLoad)
	{

		IsLoad = true;
	}

}

void Chain::Tick(float _DeltaTime)
{
}
