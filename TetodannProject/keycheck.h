//#pragma once


//���͏��p
enum KEY_ID {
	KEY_ID_SPACE,				//��߰���
	KEY_ID_1,
	KEY_ID_2,
	KEY_ID_3,
	KEY_ID_4,
	KEY_ID_MAX
};


void KeyInit(void);				//���͏��̏�����
void KeyCheck(void);			//���͏��̊m�F


//���͏��Ǘ��p
extern bool keyOld[KEY_ID_MAX];				//1�ڰёO�̓��͏��
extern bool keyNew[KEY_ID_MAX];				//���݂̓��͏��
extern bool keyDownTrigger[KEY_ID_MAX];		//�޳ݎ����ضް
extern bool keyUpTrigger[KEY_ID_MAX];		//���ߎ����ضް