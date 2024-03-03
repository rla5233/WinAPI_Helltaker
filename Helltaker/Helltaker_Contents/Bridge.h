#pragma once

// Ό³Έν :
class Bridge
{
public:
	// constructor destructor
	Bridge();
	~Bridge();
	
	// delete Function
	Bridge(const Bridge& _Other) = delete;
	Bridge(Bridge&& _Other) noexcept = delete;
	Bridge& operator=(const Bridge& _Other) = delete;
	Bridge& operator=(Bridge&& _Other) noexcept = delete;


protected:

private:

};

