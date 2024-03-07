#pragma once

#include "Character.h"

// ���� :
class Judge : public Character
{
public:
	// constructor destructor
	Judge();
	~Judge();

	// delete Function
	Judge(const Judge& _Other) = delete;
	Judge(Judge&& _Other) noexcept = delete;
	Judge& operator=(const Judge& _Other) = delete;
	Judge& operator=(Judge&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

private:


	static bool IsLoad;
};
