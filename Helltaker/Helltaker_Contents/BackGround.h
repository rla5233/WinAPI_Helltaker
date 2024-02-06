#pragma once

#include <EngineCore/Actor.h>
#include "ContentsEnum.h"


// Ό³Έν :
class BackGround : public AActor
{
public:
	// constructor destructor
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;
	
	void LoadBG();
	void SetBG();

protected:

private:
	UImageRenderer* Renderer = nullptr;

};
