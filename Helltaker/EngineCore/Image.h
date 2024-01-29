#pragma once

// Ό³Έν :
class Image
{
public:
	// constructor destructor
	Image();
	~Image();

	// delete Function
	Image(const Image& _Other) = delete;
	Image(Image&& _Other) noexcept = delete;
	Image& operator=(const Image& _Other) = delete;
	Image& operator=(Image&& _Other) noexcept = delete;

protected:

private:

};
