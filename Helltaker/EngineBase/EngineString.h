#pragma once
// 전부다 std의 헤더뿐이다.
#include <string>
#include <string_view>

// 설명 :
class EngineString
{
public:
	static std::string ToUpper(std::string_view View);

protected:

private:
	// constrcuter destructer
	EngineString();
	~EngineString();

	// delete Function
	EngineString(const EngineString& _Other) = delete;
	EngineString(EngineString&& _Other) noexcept = delete;
	EngineString& operator=(const EngineString& _Other) = delete;
	EngineString& operator=(EngineString&& _Other) noexcept = delete;
};

