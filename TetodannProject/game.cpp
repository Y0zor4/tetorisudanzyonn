#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"
#include "tetris.h"
#include "enemy.h"
#include "background.h"


int backImage;		// ｹﾞｰﾑの背景用(敵がいないところ)

int line_game;		// 列計算用変数
int combo_game;		// コンボ計算用変数
bool gameover_game;


int floor;			// 階層移動用変数
int life;			// 敵体力格納用変数
int damage;			// 敵が受けるダメージ格納用変数
int attack;			// 敵の攻撃列数

int fmCnt;			// 階層移動時のカウント
bool fmFlag;		// 階層移動中かの判断用

int gameoverCnt;		// ゲームオーバー時のカウント

// ﾀﾞﾒｰｼﾞ表示用
int damageTmp;
int damageCnt;
int damageFade;
bool damageFlag;

// ｻｳﾝﾄﾞ関係
int bgm;


bool GameSysInit(void)
{
	bool rtnFlag = true;

	if (!TetrisSysInit()) rtnFlag = false;
	if (!EnemySysInit())  rtnFlag = false;
	if (!BackgroundSysInit())  rtnFlag = false;

	backImage = LoadGraph("Image/back_tmp.png");

	bgm = LoadSoundMem("sound/bgm.mp3");

	return rtnFlag;
}

void GameInit(void)
{
	// 各制御の初期化
	TetrisInit();
	EnemyInit();
	BackgroundInit();


	floor = 1;
	damage = 0;
	life = GetEnemyLife();
	attack = 0;

	fmCnt = 0;
	fmFlag = false;
	gameover_game = false;

	damageTmp = 0;
	damageCnt = 0;
	damageFlag = false;
}

int GameScene(void)
{
	int rtn = 0;

	if (gameover_game)
	{
		gameoverCnt++;
		if (gameoverCnt == 60)
		{
			rtn = 1;
			gameoverCnt = 0;
		}
	}
	if (keyDownTrigger[KEY_ID_2])
	{
		rtn = 2;
	}
	else if (keyDownTrigger[KEY_ID_3])
	{
		rtn = 3;
	}
	else if (keyDownTrigger[KEY_ID_4])
	{
		rtn = 4;
	}

	// ﾃﾄﾘｽCtlに渡す引数は、敵から食らうそのﾌﾚｰﾑ時の攻撃のﾀﾞﾒｰｼﾞ列数
	damage = TetrisCtl(attack);
	gameover_game = Gameover();

	line_game = TetrisLine();
	combo_game = TetrisCombo();
	if (!fmFlag)
	{
		damage += DamageCalc();
	}

	// ダメージと現在の階層を引き渡す
	life = EnemyCtl(damage, floor, fmFlag);
	attack = GetAttackLines(floor);

	// ﾀﾞﾒｰｼﾞ表示用
	if (damage != 0)
	{
		damageTmp = damage;
		damageFlag = true;
		damageCnt = 0;
	}

	// 階層関連処理
	if (life <= 0 && !fmFlag)
	{
		if (!GetEnemyBlend(floor) && !GetBgBlend(floor))
		{
			fmFlag = true;
		}
	}

	BackgroundCtl(floor, fmFlag, GetEnemyBlend(floor));
	
	FloorMove();
	floor_main = floor;

	GameDraw();

	// 音再生
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, false);
	
	if (rtn != 0)
	{
		StopSoundMem(bgm);
	}
	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	BackgroundDraw(floor, GetEnemyBlend(floor));
	DrawGraph(0, 0, backImage, true);

	EnemyDraw(floor);
	TetrisDraw();
	
	DrawFormatString(1400, 90, 0xFFFFFF, "F%d", floor);

	// ﾀﾞﾒｰｼﾞ表示
	if (damageFlag)
	{
		damageCnt++;
		if (damageCnt < 150)
		{
			SetFontSize(55);
			DrawFormatString(1103, 503, 0x000000, "%d", damageTmp, true);
			DrawFormatString(1100, 500, 0xFFFFFF, "%d", damageTmp, true);
		}
		else
		{
			damageFlag = false;
		}
	}
	
	ScreenFlip();
}

int DamageCalc(void)
{
	int damage = 0;
	
	damage = DAMAGE * line_game * combo_game;

	return damage;
}

// 階層移動処理
int FloorMove(void)
{
	if (fmFlag)
	{
		if (fmCnt < FMCNT)
		{
			fmCnt++;
		}
		if (fmCnt >= FMCNT)
		{
			fmFlag = false;
			if (life <= 0)floor += 1;
			fmCnt = 0;
		}
	}
	return floor;
}