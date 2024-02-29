#include "ChapterSin.h"

bool ChapterSin::IsLoad = false;
const std::vector<const char*> ChapSin_Script1 =
{
	/* 0  Demon	    */ "???",
	/* 1  Demon	    */ "고위 기소관 저지먼트",
	/* 2  Script 1  */ "마치 천 번은 죽은 것 같은 느낌이다. 하지만 불길은\n사그라들고... 어찌됐든 당신은 아직 살아있는 것 같다.",
	/* 3  Script 2  */ "칩입자 녀석, 이제야 찾았다!\n넌	아직 죽을 수 없어.",
	/* 4  Script 3  */ "나와 함께 오랜 시간을 보내야 할 거다.",
	/* 5  Script 4  */ "죄악의 기계에 시동을 걸어라! 시련을 피할 수는 없다!",
	/* 6  Script 5  */ "침입자야, 죄악의 기계가 마음에 드느냐?",
	/* 7  Script 6  */ "이만 굴복하고 삼켜져라!",
	/* 8  Script 7  */ "희망을 버려라! 저 녀석의 운명은 이미 정해졌다!",
	/* 9  Script 8  */ "정숙하라! 이제 진짜 시작이다!",
	/* 10 Script 9  */ "너를 이곳으로 이끌었던 것들이 사슬이 되어 너를 휘감지.",
	/* 11 Script 10 */ "너의 교만, 탐욕, 그리고 욕정. 네 고통은 자초한 거다.",


};

const std::vector<const char*> ChapSin_Script2 =
{
	/* 0 Demon	  */ "세 쌍둥이 악마 케르베로스",
	/* 1 Demon	  */ "피곤한 악마 판데모니카",
	/* 2 Demon	  */ "지옥의 CEO 루시퍼",
	/* 3 Script 1 */ "안돼, 포기하지 마! 우릴 데리고 나가야지!",
	/* 4 Script 2 */ "그리고 커피도 타 주셔야죠.",
	/* 5 Script 3 */ "이런, 저지먼트. 이 녀석은 모르고 있겠지만, 내 거야. 그냥\n내버려 둘 수는 없어?",
	/* 6 Script 4 */ "그만! 고위 기소관, 즉시 물러날 것을 명한다!",

};

ChapterSin::ChapterSin()
{
}

ChapterSin::~ChapterSin()
{
}

void ChapterSin::BeginPlay()
{
	if (false == IsLoad)
	{
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialogueBG_Sin_001.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialogueBG_Sin_002.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialBG_DarkHell.png");
		ContentsHelper::LoadImg("Scene\\Dialouge", "DialBG_LitHell.png");

		IsLoad = true;
	}
}

void ChapterSin::LevelStart(ULevel * _PrevLevel)
{

}

void ChapterSin::CutSceneStart()
{}

void ChapterSin::ChangeChapter()
{}

void ChapterSin::SelectStart()
{}

void ChapterSin::SelectMenu()
{}

void ChapterSin::BadEndStart()
{}

void ChapterSin::BadEndSetting()
{}

void ChapterSin::SuccessStart()
{}
