#pragma once
#include "NameObject.h"

// 설명 : U는 그냥 엔진 속해있다는 것을 의미.
class ULevel : public UNameObject
{
public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

protected:

private:

};

