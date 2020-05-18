#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "game.h"
#include "tetris.h"
#include "enemy.h"
#include "background.h"


int backImage;   // ｹﾞｰﾑの背景用(敵がいないところ)

int line_game;
int combo_game;

int floor;
int life;
int damage;


bool GameSysInit(void)
{
	bool rtnFlag = true;

	if (!TetrisSysInit()) rtnFlag = false;
	if (!EnemySysInit())  rtnFlag = false;
	if (!BackgroundSysInit())  rtnFlag = false;

	backImage = LoadGraph("Image/back_tmp.png");

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

}

int GameScene(void)
{
	int rtn = 0;

	if (keyDownTrigger[KEY_ID_1])
	{
		rtn = 1;
	}
	else if (keyDownTrigger[KEY_ID_2])
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
	TetrisCtl(0);

	line_game = TetrisLine();
	combo_game = TetrisCombo();
	damage = DamageCalc();

	// ダメージと現在の階層を引き渡す
	life = EnemyCtl(damage, floor);


	FloorMove();

	GameDraw();

	return rtn;
}

void GameDraw(void)
{
	ClsDrawScreen();
	SetFontSize(50);
	DrawFormatString(0, 0, 0xFFFFFF, "GameScene");
	BackgroundDraw(floor);
	EnemyDraw(floor);
	DrawGraph(0, 0, backImage, true);
	TetrisDraw();
	DrawFormatString(1000, 200, 0xFFFFFF, "Damage:%d", DamageCalc());
	DrawFormatString(1400, 90, 0xFFFFFF, "F%d", floor);
	// 消した列とコンボ確認用
	DrawFormatString(900, 300, 0xFFFFFF, "line combo : %d, %d", line_game, combo_game);
	ScreenFlip();
}

int DamageCalc(void)
{
	int damage = 0;
	
	damage = DAMAGE * line_game * combo_game;

	return damage;
}

// 階層移動処理
void FloorMove(void)
{
	if (life <= 0)
	{
		floor += 1;
	}
}