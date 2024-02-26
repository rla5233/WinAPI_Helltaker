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

	std::string GetFileName() const;
	std::string GetExtension() const;

	bool IsRoot();

	void MoveParent();
	void Move(std::string_view _Path);

	std::string AppendPath(std::string_view _Path);

	std::string GetFullPath() const
	{
		// 문자열을 std에서는 char* char[100]
		// std::string을 지원해준다.
		// std::filesystem::path이 뭔지를 파악하고 경로와 관련된 편리한 기능들을 제공한다.
		// 경로라는것은 근본적으로 보자면 "C:\\aaaa\bbb\\ccc" => 문자열에 가깝다.
		// 이 경로를 담당하는 클래스는 분명히 내부에 std::string을 리턴해주는 함수가 있어야 한다.
		// 없으면 욕한다. 그런데 없을리가 없다고 생각하고
		// 못찾으면 나의 검색능력이 딸리거나 나의 센스가 부족한 경우가 많아서 잘못 생각하고 있는 경우가 많다.
		// => 커뮤니케이션 혼자 끙끙알아봐야 도움될게 없어요.
		// 그리고 회사에 저같이 까질한 사람만 대부분 착합니다.
		// 간혹가다 싸이코가 있지만 정말 
		return Path.string();
	}

protected:
	// 문자열을 잘 삭제표현할수 있어야 했다.
	// Path = C:\GM\WIn\ContentsResources\Texture\CherryBomb_0.png
	// Path = C:\GM\WIn\ContentsResources\Texture\
	// 문자열은 기본
	// std::string StringPath;
	std::filesystem::path Path;

private:
};

