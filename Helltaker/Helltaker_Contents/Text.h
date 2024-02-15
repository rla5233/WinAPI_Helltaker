#pragma once

// Ό³Έν :
class Text
{
public:
	// constructor destructor
	Text();
	~Text();
	
	// delete Function
	Text(const Text& _Other) = delete;
	Text(Text&& _Other) noexcept = delete;
	Text& operator=(const Text& _Other) = delete;
	Text& operator=(Text&& _Other) noexcept = delete;


protected:

private:

};

