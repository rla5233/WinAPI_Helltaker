#pragma once

#include "RenderActor.h"

// ���� :
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


protected:


private:

};

