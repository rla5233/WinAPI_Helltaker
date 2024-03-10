#include "SinChapter4.h"

#include "Sin_Judge.h"
#include "UI.h"

bool SinChapter4::IsLoad = false;
const std::vector<const char*> SinChapter4::SinChap4_Script =
{
	/* 0  Demon	    */ "고위 기소관 저지먼트",
	/* 1  Script 1  */ "진정한 고통이 시작되기 전에 남길 말이라도 있느냐?",
	/* 2  MenuBar1  */ "널 먼저 찾지 않은 게 후회스러워.",
	/* 3  MenuBar2  */ "너에게 형벌을 받을 수 있으니 죄악도 좋은거 같아.",

	/* 4  Script 2  */ "값싼 아부는 집어치워! 일을 어렵게 만들지 마!",
	/* 5  MenuBar1  */ "그리고 눈이 이렇게 참 예쁘잖아.",
	/* 6  MenuBar2  */ "좀 전에 헤어스타일이 좋다고 말했었나?",

	/* 7  Script 3  */ "있잖아, 나도 별로 이러고 싶진 않은데. 하지만 이미 계약이\n확정됐어. 네 저주를 막을 수 없다고.",
	/* 8  Script 4  */ "그래도... 네가 다시 지옥을 휘젓고 다니지만 않는다면 뒤로\n미룰 수는 있겠지",
	/* 9  Script 5  */ "운명은 이미 정해졌어. 난 너를 죽이고, 넌 시련을 받아야 하지.\n하지만 그게 꼭 오늘일 필요야 없어...",
	/* 10 Script 6  */ "그러니 운 좋은 줄 알고 내 눈 앞에서 사라져라!",
	/* 11 Script 7  */ "...",
	/* 12 Script 8  */ "... ...",
	/* 13 Script 9  */ "... ... ...",
	/* 14 Script 10 */ "가도 된다고 했잖아! 썩 사라져!	",
	/* 15 Script 11 */ "뭐? 네 하렘에 들어오라고? 웃기지 마라!",

	/* 16 Script 12 */ "고문으로 널 죽이려는 고통의 화신과 한 지붕 아래서\n살겠다고?",
	/* 17 MenuBar1  */ "다른건 바라지도 않아.",
	/* 18 MenuBar2  */ "내 하렘에 이미 더 나쁜 것도 있어, 정말로.",

	/* 19 Script 13 */ "뭐, 진심이야?",
	/* 20 Script 14 */ "이미 제대로 된 의례랑 거리가 먼 마당에, 더 막 나가지 못 할\n것도 없겠어.",
};

SinChapter4::SinChapter4()
{
}

SinChapter4::~SinChapter4()
{
}

void SinChapter4::BeginPlay()
{
	SinManager::BeginPlay();

	if (false == IsLoad)
	{



		AddChapterSet("SinChapter4");

		IsLoad = true;
	}
}

void SinChapter4::LevelStart(ULevel* _PrevLevel)
{
	SinManager::LevelStart(_PrevLevel);

	M_CreateSinMap(4);

	M_StateChange(ESinState::Intro);
}

void SinChapter4::Phase1_Start()
{
	SinChapterManager::Phase1_Start();
	SetPhase1_StartDelayTime(1.0f);

	M_SetSmallChainVecSize(30, ESinPhase::Phase1);

	M_CreateSmallVerChain_P1(3, 0);
	M_CreateSmallHorChain_P1(2, 0);

	M_CreateSmallVerChain_P1(2, 1);
	M_CreateSmallVerChain_P1(4, 1);
	M_CreateSmallHorChain_P1(1, 1);
	M_CreateSmallHorChain_P1(3, 1);

	M_CreateSmallVerChain_P1(0, 2);
	M_CreateSmallVerChain_P1(6, 2);
	M_CreateSmallHorChain_P1(0, 2);
	M_CreateSmallHorChain_P1(4, 2);

	M_CreateSmallVerChain_P1(0, 3);
	M_CreateSmallVerChain_P1(3, 3);
	M_CreateSmallHorChain_P1(1, 3);

	M_CreateSmallVerChain_P1(1, 4);
	M_CreateSmallVerChain_P1(4, 4);
	M_CreateSmallHorChain_P1(3, 4);

	M_CreateSmallVerChain_P1(2, 5);
	M_CreateSmallVerChain_P1(5, 5);
	M_CreateSmallHorChain_P1(2, 5);

	M_CreateSmallVerChain_P1(3, 6);
	M_CreateSmallVerChain_P1(6, 6);
	M_CreateSmallHorChain_P1(3, 6);

	M_CreateSmallVerChain_P1(0, 8);
	M_CreateSmallVerChain_P1(6, 8);

	M_CreateSmallVerChain_P1(1, 9);
	M_CreateSmallVerChain_P1(5, 9);

	M_CreateSmallVerChain_P1(2, 10);
	M_CreateSmallVerChain_P1(4, 10);

	M_CreateSmallVerChain_P1(3, 11);

	M_CreateSmallVerChain_P1(2, 12);
	M_CreateSmallVerChain_P1(4, 12);

	M_CreateSmallVerChain_P1(1, 13);
	M_CreateSmallVerChain_P1(5, 13);

	M_CreateSmallVerChain_P1(0, 14);
	M_CreateSmallVerChain_P1(6, 14);

	M_CreateSmallVerChain_P1(0, 16);
	M_CreateSmallVerChain_P1(6, 16);

	M_CreateSmallVerChain_P1(1, 17);
	M_CreateSmallVerChain_P1(5, 17);

	M_CreateSmallVerChain_P1(2, 18);
	M_CreateSmallVerChain_P1(4, 18);

	M_CreateSmallVerChain_P1(3, 19);

	M_CreateSmallVerChain_P1(0, 21);
	M_CreateSmallVerChain_P1(6, 21);
	M_CreateSmallHorChain_P1(0, 21);
	M_CreateSmallHorChain_P1(4, 21);

	M_CreateSmallVerChain_P1(1, 22);
	M_CreateSmallVerChain_P1(5, 22);
	M_CreateSmallHorChain_P1(1, 22);
	M_CreateSmallHorChain_P1(3, 22);

	M_CreateSmallVerChain_P1(3, 23);
	M_CreateSmallHorChain_P1(2, 23);

	M_CreateSmallVerChain_P1(2, 24);
	M_CreateSmallVerChain_P1(4, 24);
	M_CreateSmallHorChain_P1(0, 24);
	M_CreateSmallHorChain_P1(4, 24);

	M_CreateSmallVerChain_P1(3, 25);
	M_CreateSmallHorChain_P1(1, 25);
	M_CreateSmallHorChain_P1(3, 25);

	M_CreateSmallVerChain_P1(2, 26);
	M_CreateSmallVerChain_P1(3, 26);
	M_CreateSmallVerChain_P1(4, 26);

	M_CreateSmallVerChain_P1(0, 27);
	M_CreateSmallVerChain_P1(6, 27);
	M_CreateSmallHorChain_P1(0, 27);
	M_CreateSmallHorChain_P1(4, 27);

	M_CreateSmallVerChain_P1(0, 28);
	M_CreateSmallVerChain_P1(1, 28);
	M_CreateSmallVerChain_P1(5, 28);
	M_CreateSmallVerChain_P1(6, 28);
	M_CreateSmallHorChain_P1(2, 28);

	M_CreateSmallVerChain_P1(0, 29);
	M_CreateSmallVerChain_P1(1, 29);
	M_CreateSmallVerChain_P1(2, 29);
	M_CreateSmallVerChain_P1(4, 29);
	M_CreateSmallVerChain_P1(5, 29);
	M_CreateSmallVerChain_P1(6, 29);
}								 

void SinChapter4::Phase2_Start()
{
	SinChapterManager::Phase2_Start();

	M_CreateHitChain(ESinHitChainType::Left, 0);
	M_CreateHitChain(ESinHitChainType::Left, 2);
	M_CreateHitChain(ESinHitChainType::Right, 0);
	M_CreateHitChain(ESinHitChainType::Right, 2);
	M_CreateHitChainHp("절망의 사슬");

	M_SetSmallChainVecSize(4, ESinPhase::Phase2);

	M_CreateSmallVerChain_P2(0, 0);
	M_CreateSmallVerChain_P2(6, 0);

	M_CreateSmallHorChain_P2(0, 1);
	M_CreateSmallHorChain_P2(4, 1);

	M_CreateSmallVerChain_P2(1, 2);
	M_CreateSmallVerChain_P2(5, 2);
	M_CreateSmallHorChain_P2(0, 2);
	M_CreateSmallHorChain_P2(3, 2);

	M_CreateSmallVerChain_P2(2, 3);
	M_CreateSmallVerChain_P2(4, 3);
	M_CreateSmallHorChain_P2(1, 3);
	M_CreateSmallHorChain_P2(4, 3);
}

void SinChapter4::CutSceneStart()
{
	SinCutSceneManager::CutSceneStart();

	C_SpawnDialogue(1);

	FVector Scale = { 0.558f, 0.693f };
	FVector Pos = { 0.0f, -0.0402f };
	C_SpawnJudge("Jud_Intro_004.png", SinChap4_Script[0], Pos, Scale);
	C_GetJudge()->Character::StateChange(ECharacterState::Appear);

	C_BooperTextSet(SinChap4_Script[1]);
}

void SinChapter4::Enter(float _DeltaTime)
{
	SinCutSceneManager::Enter(_DeltaTime);

	if (UEngineInput::IsDown(VK_SPACE) || UEngineInput::IsDown(VK_RETURN))
	{
		C_StateChange(ESinSceneState::Select);
	}
}

void SinChapter4::SelectStart()
{
	SinCutSceneManager::SelectStart();

	C_MenubarTextSet(0, SinChap4_Script[2]);
	C_MenubarTextSet(1, SinChap4_Script[3]);
	OrderCount = 0;
}

void SinChapter4::SelectMenu()
{
	switch (OrderCount)
	{
	case 0:
		Select1();
		break;
	case 1:
		Select2();
		break;
	case 2:
		Select3();
		break;
	case 3:
		Select4();
		break;
	}
}

void SinChapter4::Select1()
{
	C_MenubarRenderActiveOff();
	C_BooperTextSet(SinChap4_Script[4]);
	C_GetBooper()->AllRenderersActiveOn();

	++OrderCount;
}

void SinChapter4::Select2()
{
	C_MenubarRenderActiveOn();
	C_MenubarTextSet(0, SinChap4_Script[5]);
	C_MenubarTextSet(1, SinChap4_Script[6]);
	C_GetBooper()->GetImageRenderer()->ActiveOff();

	++OrderCount;
}

void SinChapter4::Select3()
{

}

void SinChapter4::Select4()
{
}

void SinChapter4::ChangeChapter()
{
	SinManager::ChangeChapter();

}


