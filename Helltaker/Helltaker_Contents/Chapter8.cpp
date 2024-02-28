#include "Chapter8.h"

#include "Chapter9.h"
#include "BackGround.h"
#include "Character.h"
#include "Scene.h"

bool Chapter8::IsLoad = false;
const float Chapter8::SkeletonRenderDelay = 0.2f;
const float Chapter8::SkeletonCreateDelay = 0.1f;
const float Chapter8::LuSwirl1RenderDelay = 0.39f;
const float Chapter8::LuSwirl2RenderDelay = 0.6f;
const float Chapter8::LuIdleRenderDelay = 0.05f;

const std::vector<const char*> Chapter8::Chap8_Script
{
	/* 0  Demon	     */ "������ CEO �����",
	/* 1  Script 1   */ "������ ������. �� �÷õ��� ����ϸ� ��ġ�� �����߾�.",
	/* 2  Script 2   */ "��ȥ�� ��ġ�� �Ƴ��� ������ ��� �ָ�.",
	/* 3  MenuBar1_1 */ "��, ���մ�!",
	/* 4  MenuBar1_2 */ "����Ұ�. �� �Ϸ��� ���Ͷ�.",
	/* 5  Failed1    */ "�����ϰ� � ��ȥ�̷α�...",
	/* 6  Bad End1   */ "����� ������ ���� ����۴� ����� �̸��� ���� �����.\n����� ������ �״�� ��Ƴ��ȴ�.",
	/* 7  Script 3   */ "�� �Ϸ��� ����? �Ǹ��� ������ų �� ���� �Ŷ�� ������?",
	/* 8  MenuBar2_1 */ "���δ��̶�� �ҷ���. �׸��� ���� ������ ���� ����� ���ض�.",
	/* 9  MenuBar2_2 */ "Ŀ��, ���� ���� ���Ӱ� ���ݷ� ������ũ�� ������ �� ����",
	/* 10 Failed2    */ "�� ������ ������ ��߰ڱ���.",
	/* 11 Bad End2   */ "������� ������, ����� �Ǵ� ������ ���ʷ� ���ع��ȴ�.\n������ �����ϱ� ����� �����̴�.",
	/* 12 Success1   */ "����? �װ� �پ�? ������� �� ����, �� ���� ������ũ��\n �����?",
	/* 13 Success2   */ "���� ������ũ�� �����ϴ� �� ���� �� �˾ƶ�.",
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
		ContentsHelper::LoadImg("Scene\\Characters", "Lu_Swirl_Idle.png");
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
	M_BottomTextRendererOff();

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

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.046f, WinScale.Y * 0.089f };
	FVector Pos = { 0.0f, WinScale.Y * (-0.013f) };
	M_SpawnDemon({ 4, 0 }, "Lucy", { Pos, Scale });
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
	Character* Skeleton = SpawnActor<Character>(static_cast<int>(UpdateOrder::Character));
	Skeleton->SetActorLocation({ WinScale.hX(), WinScale.Y * 0.387f });
	Skeleton->SetName("Skeleton_Man");
	Skeleton->CreateImageRenderer(RenderOrder::Scene);
	Skeleton->GetImageRenderer()->SetImage("Man_Skeleton.png");
	Skeleton->GetImageRenderer()->CameraEffectOff();
	SkeletonMan.push_back(Skeleton);
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
	M_DefaultBackGround->ActiveOff();
	M_DefaultBackGround->AllRenderersActiveOff();

	C_SpawnDialogue("DialogueBG_Throne.png");
	C_SpawnCharacter("Lu", "Lu_Swirl_Idle.png");
	C_CreateCharacterAnimation("Lu_Swirl_1", "Lu_Swirl", 0, 9, 0.15f, false);
	C_CreateCharacterAnimation("Lu_Swirl_2", "Lu_Swirl", 10, 13, 0.15f, false);

	FVector WinScale = ContentsHelper::GetWindowScale();
	FVector Scale = { WinScale.X * 0.242f, WinScale.Y * 0.619f };
	FVector Pos = { 0.0f, WinScale.Y * 0.0f };
	C_GetSceneCharacter()->GetImageRenderer()->SetScale(Scale);
	C_GetSceneCharacter()->ImageRendererMoveOn({ Pos.X + (WinScale.X * 0.1f), Pos.Y }, Pos);
	
	CutSceneManager::CutSceneStart();
}

void Chapter8::EnterStart()
{
	SkeletonMan.reserve(2);
	TimeCount = LuSwirl1RenderDelay;
	EnterOrder = 0;
}

void Chapter8::Enter(float _DeltaTime)
{
	ResetCheck();
	C_GetSceneCharacter()->ImageRendererMoveUpdate(_DeltaTime, 3.5f);
	C_GetSceneCharacter()->ImageRendererFadeInUpdate(_DeltaTime);

	for (Character* Skeleton : SkeletonMan)
	{
		if (nullptr == Skeleton)
		{
			MsgBoxAssert("Acotr is nullptr");
		}

		Skeleton->ImageRendererMoveUpdate(_DeltaTime);
		Skeleton->ImageRendererFadeInUpdate(_DeltaTime);
	}

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
		EnterOrder4(_DeltaTime);
		break;
	case 5:
		EnterOrder5();
		break;
	case 6:
		EnterOrder6();
		break;
	}
}

void Chapter8::EnterOrder0(float _DeltaTime)
{
	if (false == C_GetSceneCharacter()->GetIsImageRendererMoveValue())
	{
		if (0.0f >= TimeCount)
		{
			C_ChangeCharacterAnimation("Lu_Swirl_1");
			TimeCount = SkeletonCreateDelay;
			++EnterOrder;
			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void Chapter8::EnterOrder1(float _DeltaTime)
{
	if (true == C_GetSceneCharacter()->GetImageRenderer()->IsCurAnimationEnd())
	{
		if (0.0f >= TimeCount)
		{
			SpawnSkeletonMan();
			SpawnSkeletonMan();

			FVector WinScale = ContentsHelper::GetWindowScale();
			FVector Scale = { WinScale.X * 0.3375f, WinScale.Y * 0.664f };
			FVector Pos = { WinScale.X * (-0.211f),  WinScale.Y * (-0.025f) };
			SkeletonMan[0]->GetImageRenderer()->SetScale(Scale);
			SkeletonMan[0]->ImageRendererMoveOn({ Pos.X + (WinScale.X * 0.08f), Pos.Y }, Pos);
			SkeletonMan[0]->ImageRendererFadeInOn();

			TimeCount = SkeletonRenderDelay;
			++EnterOrder;
			return;
		}

		TimeCount -= _DeltaTime;
	}
}

void Chapter8::EnterOrder2(float _DeltaTime)
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

void Chapter8::EnterOrder3(float _DeltaTime)
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

void Chapter8::EnterOrder4(float _DeltaTime)
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

void Chapter8::EnterOrder5()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_BooperTextSet(Chap8_Script[2]);
		++EnterOrder;
		SelectOrder = -1;
	}
}

void Chapter8::EnterOrder6()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		++SelectOrder;
		C_StateChange(ECutSceneState::Select);
	}
}

void Chapter8::SelectStart()
{
	CutSceneManager::SelectStart();

	switch (SelectOrder)
	{
	case 0:
		C_MenubarTextSet(0, Chap8_Script[3]);
		C_MenubarTextSet(1, Chap8_Script[4]);
		break;
	case 1:
		C_MenubarTextSet(0, Chap8_Script[8]);
		C_MenubarTextSet(1, Chap8_Script[9]);
		break;
	}
}

void Chapter8::SelectMenu()
{
	switch (C_GetFocusMenuIndex())
	{
	case 0:
		C_StateChange(ECutSceneState::BadEnd);
		break;
	case 1:
		C_StateChange(ECutSceneState::Success);
		break;
	}
}

void Chapter8::BadEndStart()
{
	CutSceneManager::BadEndStart();

	switch (SelectOrder)
	{
	case 0:
		C_BooperTextSet(Chap8_Script[5]);
		break;
	case 1:
		C_BooperTextSet(Chap8_Script[10]);
		break;
	}
}

void Chapter8::BadEndSetting()
{
	CutSceneManager::BadEndSetting();

	for (Character* Skeleton : SkeletonMan)
	{
		Skeleton->AllRenderersActiveOff();
	}

	switch (SelectOrder)
	{
	case 0 :
		C_BooperTextSet(Chap8_Script[6]);
		break;
	case 1:
		C_BooperTextSet(Chap8_Script[11]);
		break;
	}
}

void Chapter8::SuccessStart()
{
	switch (SelectOrder)
	{
	case 0:
		SuccessStart1();
		break;
	case 1:
		SuccessStart2();
		break;
	}
}

void Chapter8::SuccessStart1()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(Chap8_Script[7]);

	FVector WinScale = ContentsHelper::GetWindowScale();
	C_CharacterSetTransform({ { WinScale.X * 0.015f, WinScale.Y * 0.02f }, { WinScale.X * 0.247f, WinScale.Y * 0.561f } });
	C_CharacterSetImage("Lu_Angry.png");	
}

void Chapter8::SuccessStart2()
{
	C_MenubarRenderActiveOff();
	C_BooperImageRendererOn();
	C_BooperTextSet(Chap8_Script[12]);
}

void Chapter8::Success(float _DeltaTime)
{
	ResetCheck();

	switch (SelectOrder)
	{
	case 0:
		EnterOrder5();
		break;
	case 1:
		SuccessEnter();
		break;
	case 2:
		SuccessEndScene();
		break;
	case 3:
		CutSceneManager::Success(_DeltaTime);
		break;
	}
}

void Chapter8::SuccessEnter()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		CutSceneManager::SuccessStart();

		FVector WinScale = ContentsHelper::GetWindowScale();
		FVector CharPos = { WinScale.X * 0.015f, WinScale.Y * 0.02f };
		FVector CharScale = { WinScale.X * 0.247f, WinScale.Y * 0.561f };
		C_GetSceneCharacter()->GetImageRenderer()->SetImage("Lu_Happy.png");
		C_GetSceneCharacter()->GetImageRenderer()->SetTransform({ CharPos, CharScale });
		C_BooperTextSet(Chap8_Script[13]);
		++SelectOrder;
	}	
}

void Chapter8::SuccessEndScene()
{
	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		FVector WinScale = ContentsHelper::GetWindowScale();
		FTransform BooperTrans = { {0, 0}, { WinScale.X * 0.027f, WinScale.Y * 0.022f } };
		C_BooperChangeAnimation("Booper_Idle");
		C_BooperSetTransform(BooperTrans);
		C_BooperTextSet(Chap8_Script[14]);
		++SelectOrder;
	}
}

void Chapter8::SuccessEnd()
{
	for (Character* Skeleton : SkeletonMan)
	{
		if (nullptr == Skeleton)
		{
			MsgBoxAssert("Skeleton is nullptr");
		}

		Skeleton->AllRenderersActiveOff();
	}

	CutSceneManager::SuccessEnd();
}

void Chapter8::ChangeChapter()
{
	ChapterManager::ChangeChapter();

	CreateChapter<Chapter9>("Chapter9");
	GEngine->ChangeLevel("Chapter9");
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

	for (Character* Skeleton : SkeletonMan)
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