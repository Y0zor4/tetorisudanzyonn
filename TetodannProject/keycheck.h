//#pragma once


//入力情報用
enum KEY_ID {
	KEY_ID_SPACE,				//ｽﾍﾟｰｽｷｰ
	KEY_ID_1,
	KEY_ID_2,
	KEY_ID_3,
	KEY_ID_4,
	KEY_ID_MAX
};


void KeyInit(void);				//入力情報の初期化
void KeyCheck(void);			//入力情報の確認


//入力情報管理用
extern bool keyOld[KEY_ID_MAX];				//1ﾌﾚｰﾑ前の入力状態
extern bool keyNew[KEY_ID_MAX];				//現在の入力状態
extern bool keyDownTrigger[KEY_ID_MAX];		//ﾀﾞｳﾝ時のﾄﾘｶﾞｰ
extern bool keyUpTrigger[KEY_ID_MAX];		//ｱｯﾌﾟ時のﾄﾘｶﾞｰ