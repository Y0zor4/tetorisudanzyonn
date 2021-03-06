#include "Dxlib.h"	
#include "main.h"
#include "keycheck.h"
#include "enemy.h"

// 変数
ENEMY enemy[ENEMY_MAX];

int fmFlag_enemy;


// 敵のシステム系初期化
bool EnemySysInit(void)
{
	bool rtnFlag = true;
	enemy[0].image = LoadGraph("image/slime1.png");
	enemy[1].image = LoadGraph("image/slime2.png");
	enemy[2].image = LoadGraph("image/slime3.png");
	enemy[3].image = LoadGraph("image/slime4.png");
	enemy[4].image = LoadGraph("image/slime5.png");

	// 仮処理
	for (int e = 5; e < ENEMY_MAX; e++)
	{
		int i = rand() % 5;
		enemy[e].image = enemy[i].image;
	}


	return rtnFlag;
}

// 敵初期化
void EnemyInit(void)
{
	for (int e = 0; e < ENEMY_MAX; e++)
	{
		enemy[e].LifeMax = 100 * (e + 1);
		enemy[e].Life = enemy[e].LifeMax;
		enemy[e].Attack = 1;
		// ｶｳﾝﾄ値の設定
		if ((e + 1) % 10 < 6 && (e + 1) != 0)
		{
			enemy[e].CntMax = 600;
		}
		else if ((e + 1) % 10 > 5 || (e + 1) == 0)
		{
			enemy[e].CntMax = 400;
		}
		if ((e + 1) > 30)
		{
			enemy[e].CntMax = 300;
		}
		enemy[e].Cnt = enemy[e].CntMax;
		enemy[e].Appear = 0;
	}

	fmFlag_enemy = false;
}

// 敵の行動制御
int EnemyCtl(int damage, int floor, bool flag)
{
	fmFlag_enemy = flag;
	if (fmFlag_enemy)
	{
		return 0;
	}

	int i, j, R;
	// 敵体力減少処理
	if (enemy[floor - 1].Life > 0)
	{
		enemy[floor - 1].Life = enemy[floor - 1].Life - damage;
	
	}
	
	if (enemy[floor - 1].Life <= 0)
	{
		enemy[floor - 1].Life = 0;
		flag = false;
	}
	
	return enemy[floor - 1].Life;
}

// 敵の描画
void EnemyDraw(int floor)
{

	if (enemy[floor - 1].Life > 0)
	{
		enemy[floor - 1].Appear += 10;
		if (enemy[floor - 1].Appear >= 255)
		{
			enemy[floor - 1].Appear = 255;
		}
	}
	else
	{
		enemy[floor - 1].Appear -= 2;
		if (enemy[floor - 1].Appear <= 0)
		{
			enemy[floor - 1].Appear = 0;
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, enemy[floor - 1].Appear);
	DrawGraph(712, 176, enemy[floor - 1].image, true);
	//DrawBox(1000, 500, 1200, 800, 0xFFFFFF, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	if (fmFlag_enemy)
	{
		return;
	}
	

	// 敵の体力ゲージ (後に変更有)
	DrawBox(750, 90, 1350, 130, 0x000000, true);
	DrawBox(750, 90, 600 * enemy[floor - 1].Life / enemy[floor - 1].LifeMax + 750, 130, 0x00FF00, true);
	DrawBox(750, 90, 1350, 130, 0xFFFFFF, false);

	// 敵の攻撃ゲージ（後に変更有）
	DrawBox(800, 820, 1400, 850, 0x000000, true);
	DrawBox(800, 820, 600 * enemy[floor - 1].Cnt / enemy[floor - 1].CntMax + 800, 850, 0xFF0000, true);
	DrawBox(800, 820, 1400, 850, 0xFFFFFF, false);

	
	// 敵の体力数値
	DrawFormatString(900, 30, 0xFFFFFF, "HP:%d/%d", enemy[floor - 1].Life, enemy[floor - 1].LifeMax);




}


int GetEnemyLife(void)
{
	return enemy[0].LifeMax;
}

int GetAttackLines(int floor)
{
	if (fmFlag_enemy)
	{
		return 0;
	}

	
	if (enemy[floor - 1].Appear == 255)
	{
		// 敵の攻撃関連
		if (enemy[floor - 1].Cnt > 0)enemy[floor - 1].Cnt--;

		if (enemy[floor - 1].Cnt <= 0)
		{
			enemy[floor - 1].Cnt = enemy[floor - 1].CntMax;
			
			if (floor > 10 && floor <= 20) enemy[floor - 1].Attack = 2;
			else if (floor > 20 && floor <= 30) enemy[floor - 1].Attack = 3;
			else if (floor > 30 && floor <= 40) enemy[floor - 1].Attack = 4;
			else if (floor > 40 && floor <= 49) enemy[floor - 1].Attack = 5;
			else if (floor == 50) enemy[floor - 1].Attack = 6;

			return enemy[floor - 1].Attack;
		}
	}
	return 0;
}



// 現在の敵の表示状態を返す。
bool GetEnemyBlend(int floor)
{
	if (enemy[floor - 1].Appear == 0)
	{
 		return false;
	}
	return true;
}

