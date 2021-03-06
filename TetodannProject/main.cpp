#include "Dxlib.h"	
#include <string.h>
#include "main.h"
#include "init.h"
#include "keycheck.h"
#include "title.h"
#include "story.h"
#include "name.h"
#include "select.h"
#include "game.h"
#include "gameover.h"
#include "gameclear.h"
#include "ranking.h"
#include "fade.h"

// ｼｽﾃﾑ関連
SCENE_ID scnID;					// 現在のｼｰﾝ格納用
int nextscn;					// 次のｼｰﾝ移動先決定用
int floor_main;
char name[256];


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ｼｽﾃﾑの初期化
	if (!SysInit())
	{
		return -1;
	}
	//変数の初期化
	scnID = SCENE_ID_TITLE;


	// ｹﾞｰﾑﾙｰﾌﾟ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();	//画面消去

		//入力情報の確認
		KeyCheck();

		switch (scnID)
		{
		case SCENE_ID_TITLE:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			
			}
			nextscn = TitleScene();
			if (nextscn == 1)
			{
				StoryInit();
				scnID = SCENE_ID_STORY;
			}
			break;

		case SCENE_ID_STORY:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}
			nextscn = StoryScene();
			if (nextscn == 1)
			{
				NameInit();
				scnID = SCENE_ID_NAME;
			}
			break;

		case SCENE_ID_NAME:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}
			nextscn = NameScene();
			if (nextscn == 1)
			{
				SelectInit();
				scnID = SCENE_ID_SELECT;
			}
			break;

		case SCENE_ID_SELECT:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}

			nextscn = SelectScene();

			if (nextscn == 1)
			{

				GameInit();
				scnID = SCENE_ID_GAME;
			}
			else if (nextscn == 2)
			{

				TitleInit();
				scnID = SCENE_ID_TITLE;
			}
			break;

		case SCENE_ID_GAME:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}
			nextscn = GameScene();
			if (nextscn == 1)
			{
				GameoverInit();
				scnID = SCENE_ID_GAMEOVER;
			}
			else if (nextscn == 2)
			{
				GameclearInit();
				scnID = SCENE_ID_GAMECLEAR;
			}
			else if (nextscn == 3)
			{
				SelectInit();
				scnID = SCENE_ID_SELECT;
			}
			else if (nextscn == 4)
			{
				TitleInit();
				scnID = SCENE_ID_TITLE;
			}
			break;

		case SCENE_ID_GAMEOVER:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}
			nextscn = GameoverScene();
			if (nextscn == 1)
			{
				RankingInit();
				scnID = SCENE_ID_RANKING;
			}
			break;

		case SCENE_ID_GAMECLEAR:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}
			nextscn = GameclearScene();
			if (nextscn == 1)
			{
				RankingInit();
				scnID = SCENE_ID_RANKING;
			}
			break;

		case SCENE_ID_RANKING:
			if (fadein)
			{
				if (!FadeIn(5))
				{
					fadeout = false;
				}	//エフェクト後の終了後の処理
			}
			else if (fadeout)
			{
				if (!FadeOut(5))
				{	//エフェクト後の終了後の処理
					fadein = true;
				}
			}
			nextscn = RankingScene();
			if (nextscn == 1)
			{
				SelectInit();
				scnID = SCENE_ID_SELECT;
			}
			else if (nextscn == 2)
			{
				TitleInit();
				scnID = SCENE_ID_TITLE;
			}

			break;

		default:
			break;
		}
	}
	DxLib_End(); // DxLibの終了

	return true;
}

