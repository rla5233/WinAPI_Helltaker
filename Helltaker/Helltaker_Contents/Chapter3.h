#pragma once

// Ό³Έν :
class Chapter3
{
public:
	// constructor destructor
	Chapter3();
	~Chapter3();
	
	// delete Function
	Chapter3(const Chapter3& _Other) = delete;
	Chapter3(Chapter3&& _Other) noexcept = delete;
	Chapter3& operator=(const Chapter3& _Other) = delete;
	Chapter3& operator=(Chapter3&& _Other) noexcept = delete;


protected:

private:

};

