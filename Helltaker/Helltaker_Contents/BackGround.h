#pragma once

#include <EngineCore/Actor.h>


// ���� :
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
	
	void LoadImg();
	void SetImg();

protected:

private:
	UImageRenderer* Renderer = nullptr;

};
