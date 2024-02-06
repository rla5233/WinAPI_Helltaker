#pragma once
#include <EngineCore\EngineCore.h>

// Ό³Έν :
class Helltaker_ContentsCore : public UEngineCore
{
public:
	// constructor destructor
	Helltaker_ContentsCore();
	~Helltaker_ContentsCore();

	// delete Function
	Helltaker_ContentsCore(const Helltaker_ContentsCore& _Other) = delete;
	Helltaker_ContentsCore(Helltaker_ContentsCore&& _Other) noexcept = delete;
	Helltaker_ContentsCore& operator=(const Helltaker_ContentsCore& _Other) = delete;
	Helltaker_ContentsCore& operator=(Helltaker_ContentsCore&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;

private:

};
