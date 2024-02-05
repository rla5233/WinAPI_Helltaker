#pragma once

#include <EngineCore/Actor.h>
#include "ContentsEnum.h"


// 설명 :
class BackGround : public AActor
{
public:
	// constructor destructor
	BackGround();
	~BackGround();

	// delete Function
	BackGround(const BackGround& _Other) = delete;
	BackGround(BackGround&& _Other) noexcept = delete;
	BackGround& operator=(const BackGround& _Other) = delete;
	BackGround& operator=(BackGround&& _Other) noexcept = delete;
	
	//void Set_BG_Image(std::string_view _Name);
	//void Set_BG_Transform(const FTransform& _Value);
	//void Create_BG_ImageRenderer(int _Order);

	// 여기 부터 Test
	//UEngineDirectory ResourcesPath = UEngineDirectory();
	//ResourcesPath.MoveParent();
	//ResourcesPath.Move("Resources\\Characters\\Chapter\\Hero");
	//UEngineResourcesManager::GetInst().LoadFolder(ResourcesPath.AppendPath("Right_Idle"));
	//
	//Renderer = CreateImageRenderer(1);
	//Renderer->SetImage("Right_Idle");
	//Renderer->SetTransform({ {0,0}, {90, 90} });

protected:

private:
	UImageRenderer* Renderer = nullptr;

};
