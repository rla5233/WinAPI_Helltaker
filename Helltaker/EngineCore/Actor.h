#pragma once

// 설명 : A가 붙은 오브젝트는 화면에 위치가 존재해야한다.
class AActor
{
public:
	// constrcuter destructer
	AActor();
	~AActor();

	// delete Function
	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

protected:

private:

};

