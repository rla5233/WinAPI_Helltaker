#include "EngineResourcesManager.h"
#include <EnginePlatform\WindowImage.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>
#include "EngineCore.h"
#include "EngineBase\EngineDebug.h"

//UEngineResourcesManager UEngineResourcesManager::Inst;
//UEngineResourcesManager* UEngineResourcesManager::pInst = nullptr;

UEngineResourcesManager::UEngineResourcesManager()
{
}

UEngineResourcesManager::~UEngineResourcesManager()
{
	for (std::pair<const std::string, UWindowImage*>& Pair : Images)
	{
		delete Pair.second;
		Pair.second = nullptr;
	}

	Images.clear();
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadImg(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadImg(std::string_view _Path, std::string_view _Name)
{
	// 모든 이름은 대문자로
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Images.contains(UpperName))
	{
		// 에디터 모드나 디버그에서는 속력을 따질필요가 없다.
		// 게임에서 실제 실행되지 않을 내용에 대해서는 속력을 따지지 않는다.
		MsgBoxAssert(std::string("경로 : ") + std::string(_Path) + "파일명 : " + std::string(_Name) + "이미 로드한 파일을 또 로드하려고 했습니다");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->Load(GEngine->MainWindow.GetWindowImage());

	// .Png .bmp => 확장자만 바꾸면 png가 bmp가 된다고 생각했던 학생이 있었는데 아닙니다.
	// 제대로 이미지 편집 프로그램에서 포맷을 변경하고 저장하셔야 합니다.
	// 일단 winapi는 기본적으로 png를 출력하는 함수를 지원하지 않습니다.
	// 무조건 bmp만 됩니다.
	// .Png를 로드해서 bmp로 변경해서 출력할 겁니다. => 처음합니다.
	// 그래서 Png를 출력하는것도 아니고 부분 반투명
	Images[UpperName] = NewImage;

	return nullptr;

}

void UEngineResourcesManager::UnloadImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == Images.contains(UpperName))
	{
		MsgBoxAssert("이미지명 : " + std::string(_Name) + "존재하지 않는 이미지를 언로드하려고 했습니다");
		return;
	}

	UWindowImage* Image = Images[UpperName];
	Images.erase(UpperName);
	delete Image;
}

bool UEngineResourcesManager::IsImage(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);
	return Images.contains(UpperName);
}

UWindowImage* UEngineResourcesManager::FindImg(std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (false == Images.contains(UpperName))
	{
		MsgBoxAssert("파일명 : " + std::string(_Name) + "은 존재하지 않는 이미지입니다");
		return nullptr;
	}

	return Images[UpperName];
}

void UEngineResourcesManager::CuttingImage(std::string_view _Name, int _X, int _Y)
{
	UWindowImage* FindImage = FindImg(_Name);

	if (nullptr == FindImage)
	{
		MsgBoxAssert("파일명 : " + std::string(_Name) + "존재하지 않는 이미지를 커팅하려고 했습니다");
	}

	FindImage->Cutting(_X, _Y);
}

UWindowImage* UEngineResourcesManager::LoadFolder(std::string_view _Path)
{
	UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
	std::string FileName = NewPath.GetFileName();
	return LoadFolder(_Path, FileName);
}

UWindowImage* UEngineResourcesManager::LoadFolder(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Images.contains(UpperName))
	{
		MsgBoxAssert(std::string("경로 : ") + std::string(_Path) + "파일명 : " + std::string(_Name) + "이미 로드한 파일을 또 로드하려고 했습니다");
		return nullptr;
	}

	UWindowImage* NewImage = new UWindowImage();
	NewImage->SetName(UpperName);
	NewImage->SetPath(_Path);
	NewImage->LoadFolder(GEngine->MainWindow.GetWindowImage());

	// .Png .bmp => 확장자만 바꾸면 png가 bmp가 된다고 생각했던 학생이 있었는데 아닙니다.
	// 제대로 이미지 편집 프로그램에서 포맷을 변경하고 저장하셔야 합니다.
	// 일단 winapi는 기본적으로 png를 출력하는 함수를 지원하지 않습니다.
	// 무조건 bmp만 됩니다.
	// .Png를 로드해서 bmp로 변경해서 출력할 겁니다. => 처음합니다.
	// 그래서 Png를 출력하는것도 아니고 부분 반투명
	Images[UpperName] = NewImage;

	return NewImage;
}