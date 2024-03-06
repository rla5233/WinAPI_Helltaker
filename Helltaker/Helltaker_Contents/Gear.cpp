#include "Gear.h"

bool Gear::IsLoad = false;
const FVector Gear::Scale = { 0.208f, 0.278f };
const float Gear::WorkingInter = 0.016f;

Gear::Gear()
{
}

Gear::~Gear()
{
}

void Gear::BeginPlay()
{
	RenderActor::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_LGears_001.png");
		ContentsHelper::LoadImg("Chapter\\Component\\Sin_Gear", "Sin_RGears_001.png");
		
		ContentsHelper::LoadFolder("Chapter\\Component\\Sin_Gear", "Sin_LGear");
		ContentsHelper::LoadFolder("Chapter\\Component\\Sin_Gear", "Sin_RGear");

		IsLoad = true;
	}

	L_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);
	R_ImageRenderer = CreateImageRenderer(SinRenderOrder::Bottom);

	std::vector<float> _Inters;
	for (int i = 0; i <= 14; i++)
	{
		if (i < 8)
		{
			_Inters.push_back(0.016f * (8 - i));
		}
		else
		{
			_Inters.push_back(0.016f);
		}
	}

	std::vector<int> _Index;
	for (int i = 0; i <= 14; i++)
	{
		_Index.push_back(i);
	}

	L_ImageRenderer->SetImage("Sin_LGear");
	L_ImageRenderer->CreateAnimation("L_Working", "Sin_LGear", 0, 14, WorkingInter, true);
	L_ImageRenderer->CreateAnimation("L_WorkingSlow", "Sin_LGear", _Index, _Inters, false);

	R_ImageRenderer->SetImage("Sin_RGear");
	R_ImageRenderer->CreateAnimation("R_Working", "Sin_RGear", 0, 14, WorkingInter, true);
	R_ImageRenderer->CreateAnimation("R_WorkingSlow", "Sin_RGear", _Index, _Inters, false);
	
	std::reverse(_Inters.begin(), _Inters.end());
	L_ImageRenderer->CreateAnimation("L_Stop", "Sin_LGear", _Index, _Inters, false);
	R_ImageRenderer->CreateAnimation("R_Stop", "Sin_RGear", _Index, _Inters, false);
}

void Gear::IdleStart()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	float PosX = WinScale.X * 0.396f;
	
	L_ImageRenderer->SetImage("Sin_LGears_001.png");
	L_ImageRenderer->SetTransform({ { -PosX, 0.0f } , WinScale * Scale });
	
	R_ImageRenderer->SetImage("Sin_RGears_001.png");
	R_ImageRenderer->SetTransform({ { PosX, 0.0f } , WinScale * Scale });
}

void Gear::Idle(float _DeltaTime)
{
}

void Gear::WorkingStart()
{
	L_ImageRenderer->AnimationReset();
	L_ImageRenderer->ChangeAnimation("L_WorkingSlow");

	R_ImageRenderer->AnimationReset();
	R_ImageRenderer->ChangeAnimation("R_WorkingSlow");

	WorkOrder = 0;
}

void Gear::Working(float _DeltaTime)
{
	switch (WorkOrder)
	{
	case 0:
		Working1();
		break;
	}
}

void Gear::Working1()
{
	if (true == L_ImageRenderer->IsCurAnimationEnd())
	{
		L_ImageRenderer->AnimationReset();
		L_ImageRenderer->ChangeAnimation("L_Working");	
		
		R_ImageRenderer->AnimationReset();
		R_ImageRenderer->ChangeAnimation("R_Working");
		++WorkOrder;
	}
}

void Gear::StopStart()
{
	StopOrder = 0;
}

void Gear::Stop(float _DeltaTime)
{
	switch (StopOrder)
	{
	case 0:
		Stop1();
		break;
	case 1:
		Stop2();
		break;
	}
}

void Gear::Stop1()
{
	if (0 == L_ImageRenderer->GetCurAnimationFrame())
	{
		L_ImageRenderer->AnimationReset();
		L_ImageRenderer->ChangeAnimation("L_Stop");

		R_ImageRenderer->AnimationReset();
		R_ImageRenderer->ChangeAnimation("R_Stop");
		++StopOrder;
	}
}

void Gear::Stop2()
{
	if (true == L_ImageRenderer->IsCurAnimationEnd())
	{
		StateChange(ESinGearState::Idle);
	}
}

void Gear::Tick(float _DeltaTime)
{
	RenderActor::Tick(_DeltaTime);

	StateUpdate(_DeltaTime);
}

void Gear::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case ESinGearState::Idle:
		Idle(_DeltaTime);
		break;
	case ESinGearState::Working:
		Working(_DeltaTime);
		break;
	case ESinGearState::Stop:
		Stop(_DeltaTime);
		break;
	}
}

void Gear::StateChange(ESinGearState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case ESinGearState::Idle:
			IdleStart();
			break;
		case ESinGearState::Working:
			WorkingStart();
			break;
		case ESinGearState::Stop:
			StopStart();
			break;
		}
	}
	
	State = _State;	
}