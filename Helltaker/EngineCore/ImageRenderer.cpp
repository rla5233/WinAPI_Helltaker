#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"
#include <EngineCore\EngineResourcesManager.h>

UImageRenderer::UImageRenderer()
{}

UImageRenderer::~UImageRenderer()
{}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;
	// 나의 오더가 바뀌기전에 혹시나 내가 어떤 그룹에 속해있다면
	// 그 그룹에서 빠져 나온다.
	Renderers[GetOrder()].remove(this);

	// 나의 오더가 바뀐다.
	UTickObject::SetOrder(_Order);

	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (nullptr == Image)
	{
		MsgBoxAssert("이미지가 존재하지 않는 랜더러 입니다");
	}

	// 위에서부터 읽어야 합니다.
	FTransform ThisTrans = GetTransform();

	// 액터인데 지금 의미가 없습니다.
	FTransform OwnerTrans = GetOwner()->GetTransform();

	// 컴포넌트의 위치는 부모에게서 상대적이기 때문에.
	// 부모의 위치를 더해줘야 한다.
	ThisTrans.AddPosition(OwnerTrans.GetPosition());


	// 이려면 윈도우 이미지에 그리면 화면의 갱신이 산발적으로 일어나므로
	// GEngine->MainWindow.GetWindowImage()->BitCopy(Image, ThisTrans);

	// 
	// GEngine->MainWindow.GetBackBufferImage()->BitCopy(Image, ThisTrans);
	// Rectangle(WindowDC, ThisTrans.iLeft(), ThisTrans.iTop(), ThisTrans.iRight(), ThisTrans.iBottom());

	// 1, 0, 0, 255

	// 여기입니다.

	GEngine->MainWindow.GetBackBufferImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform);

}

void UImageRenderer::BeginPlay()
{
	// 부모것을 실행시켜주는 습관을 들이자.
	USceneComponent::BeginPlay();
}

void UImageRenderer::SetImage(std::string_view _Name)
{
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	if (nullptr == Image)
	{
		// 예외를 출력하게 하는것도 중요하다.
		MsgBoxAssert(std::string(_Name) + "이미지가 존재하지 않습니다.");
		return;
	}
}