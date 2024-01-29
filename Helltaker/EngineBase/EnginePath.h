#pragma once
#include <string>
#include <filesystem> 
// C++표준 파일 경로 관리가 나왔습니다.
// 함수만 호출해도 그냥 경로가 튀어 나오는 
// 편리한 기능을 대거 지원하게 되었습니다.

// 설명 : 파일 경로의 편집과 이동 등등을 처리한다.
class UEnginePath
{
public:
	// constrcuter destructer
	UEnginePath();
	UEnginePath(std::filesystem::path _Path);
	~UEnginePath();

	//// delete Function
	//UEnginePath(const UEnginePath& _Other) = delete;
	//UEnginePath(UEnginePath&& _Other) noexcept = delete;
	//UEnginePath& operator=(const UEnginePath& _Other) = delete;
	//UEnginePath& operator=(UEnginePath&& _Other) noexcept = delete;

	// 이게 파일경로인지.
	bool IsFile();
	bool IsDirectory();

	bool IsExists();

	void MoveParent();
	void Move(std::string_view _Path);

protected:
	// 문자열을 잘 삭제표현할수 있어야 했다.
	// Path = C:\GM\WIn\ContentsResources\Texture\CherryBomb_0.png
	// Path = C:\GM\WIn\ContentsResources\Texture\
	// 문자열은 기본
	// std::string StringPath;
	std::filesystem::path Path;

private:
};

