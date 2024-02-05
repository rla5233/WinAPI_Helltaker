#pragma once

// Ό³Έν :
class ContentsHelper
{
public:
	// constructor destructor
	ContentsHelper();
	~ContentsHelper();

	// delete Function
	ContentsHelper(const ContentsHelper& _Other) = delete;
	ContentsHelper(ContentsHelper&& _Other) noexcept = delete;
	ContentsHelper& operator=(const ContentsHelper& _Other) = delete;
	ContentsHelper& operator=(ContentsHelper&& _Other) noexcept = delete;

protected:

private:

};
