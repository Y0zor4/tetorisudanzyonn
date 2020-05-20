//#pragma once

#define ENEMY_MAX 50


struct ENEMY
{
	int Life;				// �G�̌��݂̗̑�
	int LifeMax;			// �G�̗͍̑ő�l
	int Attack;				// �G�̍U���́i�e�g���~�m�̏o���񐔁j
	int Cnt;				// �G���̍U�����x�p�J�E���g
	int CntMax;				// �G���̍U���J�E���g�ő吔
	int Flag;
};

bool EnemySysInit(void);
void EnemyInit(void);
int EnemyCtl(int damage, int floor, bool flag);
void EnemyDraw(int floor);
int GetEnemyLife(void);
int GetAttackLines(int floor);
