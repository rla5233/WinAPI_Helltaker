#include "Chapter8.h"

#include "BackGround.h"
#include "Character.h"
#include "Scene.h"

bool Chapter8::IsLoad = false;
const float Chapter8::SkeletonRenderDelay = 0.2f;
const float Chapter8::SkeletonCreateDelay = 0.15f;
const float Chapter8::LuSwirl2RenderDelay = 0.6f;
const float Chapter8::LuIdleRenderDelay = 0.05f;

const std::vector<const char*> Chap8_Script
{
	/* 0  Demon	     */ "������ CEO �����",
	/* 1  Script 1   */ "������ ������. �� �÷õ��� ����ϸ� ��ġ�� �����߾�.",
	/* 2  Script 2   */ "��ȥ�� ��ġ�� �Ƴ��� ������ ��� �ָ�.",
	/* 3  MenuBar1_1 */ "��, ���մ�!",
	/* 4  MenuBar1_2 */ "������. �� �Ϸ��� ���Ͷ�.",
	/* 5  Failed1    */ "�����ϰ� � ��ȥ�̷α�...",
	/* 6  Bad End1   */ "����� ������ ���� ����۴� ����� �̸��� ���� �����.\n����� ������ �״�� ��Ƴ��ȴ�.",
	/* 7  Script 3   */ "�� �Ϸ��� ����? �Ǹ��� ������ų �� ���� �Ŷ�� ������?",
	/* 8  MenuBar2_1 */ "���δ��̶�� �ҷ���. �׸��� ���� ������ ���� ����� ���ض�.",
	/* 9  MenuBar2_2 */ "Ŀ��, ���� ���� ���Ӱ� ���ݷ� ������ũ�� ������ �� ����",
	/* 10 Failed2    */ "�� ������ ������ ��߰ڱ���.",
	/* 11 Bad End2   */ "������� ������, ����� �Ǵ� ������ ���ʷ� ���ع��ȴ�.\n������ �����ϱ� ����� �����̴�.",
	/* 12 Success1   */ "����? �װ� �پ�? ������� �� ����, �� ���� ������ũ��\n �����?"
	/* 13 Success2   */ "���� ������ũ�� �����ϴ� �� ���� �� �˾ƶ�."
	/* 14 Success3   */ "�׷� ����� �� ����. ��¼�� �� �Ϸ��̶�� �� ����� ����\n�ְھ�."
};

Chapter8::Chapter8()
{
}

Chapter8::~Chapter8()
{
}

void Chapter8::BeginPlay()
{
	HellTakerManager::BeginPlay();

	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("BackGround", "ChapterBG_008.png");
		ContentsHelper::LoadImg("Scene\\Dialogue", "DialogueBG_Throne.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Man_Skeleton.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Idle.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Angry.png");
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Happy.png");
		ContentsHelper::LoadFolder("Chapter\\Demon", "Lucy");
		ContentsHelper::LoadFolder("Scene\\Characters", "Lu_Swirl");

		AddChapterSet("Chapter8");
		IsLoad = true;
	}
}

void Chapter8::LevelStart(ULevel * _PrevLevel)
{
	ChapterManager::LevelStart(_PrevLevel);

	// �������� ����
	std::vector<std::vector<bool>> Map =
	{
		{ false, false, false, false, false, false, false, false, false },
		{ true , true , false, false, false, false, false, true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ true , true , false, true , true , true , false, true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ true , true , false, true , true , true , false, true , true  },
		{ true , true , true , true , true , true , true , true , true  },
		{ false, true , false, true , true , true , false, true , false },
		{ false, true , true , true , true , true , true , true , false },
		{ false, true , false, true , true , true , false, true , false },
		{ false, true , true , true , true , true , true , true , false },
		{ false, false, false, true , true , true , false, false, false }
	};

	M_CreateTileInfoVec(Map);
	M_SetChapterStartLocation({ 0.265f, 0.115f });
	M_SetCameraPosUpdate(true);

	CreateDefaultBG();
	CreateBG("ChapterBG_008");
	M_CreateChapterUI(8);

	M_SpawnHero({ 4, 11 }, 12);

	M_SpawnSkeleton({ 4, 2 });
	M_SpawnSkeleton({ 4, 3 });
	M_SpawnSkeleton({ 4, 4 });
	M_SpawnSkeleton({ 4, 5 });
	M_SpawnSkeleton({ 4, 6 });
	M_SpawnSkeleton({ 4, 7 });
	M_SpawnSkeleton({ 4, 8 });
	M_SpawnSkeleton({ 4, 9 });

	M_SetIsThornChange(false);

	M_SpawnDemon({ 4, 0 }, "Lucy");
	EndPoint = { 4, 2 };

	M_StateChange(EChapterState::Idle);

#ifdef DEBUG
	ShowLocationPoint();
#endif
}

void Chapter8::CreateDefaultBG()
{
	M_DefaultBackGround = SpawnActor<BackGround>(static_cast<int>(UpdateOrder::BackGround));
	M_DefaultBackGround->CreateBackGround("DefaultBG");
	M_DefaultBackGround->GetImageRenderer()->CameraEffectOff();
}

void Chapter8::SpawnSkeletonMan()
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	Scene* Skeleton = SpawnActor<Scene>(static_cast<int>(UpdateOrder::Scene));
	Skeleton->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.387f });
	Skeleton->SetName("Skeleton_Man");
	Skeleton->CreateImageRenderer(RenderOrder::Scene);
	Skeleton->GetImageRenderer()->SetImage("Man_Skeleton.png");
	Skeleton->GetImageRenderer()->CameraEffectOff();
	SkeletonMan.push_back(Skeleton);
}

void Chapter8::LevelEnd(ULevel* _NextLevel)
{
	CutSceneManager::LevelEnd(_NextLevel);

	if (nullptr == M_DefaultBackGround)
	{
		MsgBoxAssert("BackGround is nullptr.")
	}

	M_DefaultBackGround->Destroy();
	M_DefaultBackGround = nullptr;

	for (Scene* Skeleton : SkeletonMan)
	{
		if (nullptr == Skeleton)
		{
			MsgBoxAssert("Skeleton is nullptr.");
		}

		Skeleton->Destroy();
		Skeleton = nullptr;
	}

	SkeletonMan.clear();
}

void Chapter8::CutSceneCheck()
{
	if (M_GetHeroLocationPoint() == EndPoint)
	{
		M_StateChange(EChapterState::CutScene);
	}
}

void Chapter8::CutSceneStart()
{
	CutSceneManager::CutSceneStart();

	M_DefaultBackGround->ActiveOff();
	M_DefaultBackGround->AllRenderersActiveOff();

	C_SpawnDialogue("DialogueBG_Throne.png");
	C_SpawnCharacter("Lu", "Lu_Swirl");
	C_CreateCharacterAnimation("Lu_Swirl_1", "Lu_Swirl", 0, 9, 0.15f, false);
	C_CreateCharacterAnimation("Lu_Swirl_2", "Lu_Swirl", 10, 13, 0.15f, false);
	C_ChangeCharacterAnimation("Lu_Swirl_1");

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { 0.0f, WinScale.Y * 0.0f}, {WinScale.X * 0.242f, WinScale.Y * 0.619f} });
}

void Chapter8::EnterStart()
{
	SkeletonMan.reserve(2);
	TimeCount = SkeletonCreateDelay;
	EnterOrder = 0;
}

void Chapter8::Enter(float _DeltaTime)
{
	ResetCheck();

	switch (EnterOrder)
	{
	case 0 :
		EnterOrder0(_DeltaTime);
		break;
	case 1 :
		EnterOrder1(_DeltaTime);
		break;
	case 2:
		EnterOrder2(_DeltaTime);
		break;
	case 3:
		EnterOrder3(_DeltaTime);
		break;
	case 4:
		EnterOrder4();
		break;
	}
}

void Chapter8::EnterOrder0(float _DeltaTime)
{
	if (true == C_GetSceneCharacter()->GetImageRenderer()->IsCurAnimationEnd())
	{
		if (0 >= TimeCount)
		{
			SpawnSkeletonMan();	
			SpawnSkeletonMan();

			FVector WinScale = ContentsHelper::GetWindowScale();
			FVector SkeletonScale = { WinScale.X * 0.3375f, WinScale.Y * 0.664f };
			SkeletonMan[0]->GetImageRenderer()->SetTransform({ { WinScale.X * (-0.211f),  WinScale.Y * (-0.025f) }, SkeletonScale });

			TimeCount = SkeletonRenderDelay;
			++EnterOrder;
			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void Chapter8::EnterOrder1(float _DeltaTime)
{
	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector SkeletonScale = { WinScale.X * 0.3375f, WinScale.Y * 0.664f };

	if (0.0f >= TimeCount)
	{
		SkeletonMan[1]->GetImageRenderer()->SetTransform({ { WinScale.X * 0.211f, WinScale.Y * (-0.025f) }, SkeletonScale });		

		TimeCount = LuSwirl2RenderDelay;
		++EnterOrder;
		return;
	}

	TimeCount -= _DeltaTime;
}

void Chapter8::EnterOrder2(float _DeltaTime)
{
	if (0.0f >= TimeCount)
	{
		C_ChangeCharacterAnimation("Lu_Swirl_2");

		TimeCount = LuIdleRenderDelay;
		++EnterOrder;
		return;
	}

	TimeCount -= _DeltaTime;
}

void Chapter8::EnterOrder3(float _DeltaTime)
{
	if (true == C_GetSceneCharacter()->GetImageRenderer()->IsCurAnimationEnd())
	{
		if (0.0f >= TimeCount)
		{
			FVector WinScale = ContentsHelper::GetWindowScale();
			C_GetSceneCharacter()->GetImageRenderer()->AnimationReset();
			C_GetSceneCharacter()->GetImageRenderer()->SetImage("Lu_Idle.png");
			C_GetSceneCharacter()->GetImageRenderer()->SetTransform({ { 0.0f, WinScale.Y * (-0.017f) }, {WinScale.X * 0.222f, WinScale.Y * 0.639f} });
			C_GetSceneCharacter()->GetNameRenderer()->SetText(Chap8_Script[0]);
			
			C_SpawnBooper();
			C_BooperTextSet(Chap8_Script[1]);

			++EnterOrder;
		}

		TimeCount -= _DeltaTime;
	}
}

void Chapter8::EnterOrder4()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Chap8_Script[2]);
	}
}

void Chapter8::SelectStart()
{

}

void Chapter8::SelectMenu()
{

}

void Chapter8::BadEndStart()
{

}

void Chapter8::BadEndSetting()
{

}

void Chapter8::SuccessStart()
{

}

void Chapter8::ChangeChapter()
{

}

