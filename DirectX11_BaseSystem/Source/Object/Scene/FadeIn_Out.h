#ifndef __FADEIN_OUT__
#define __FADEIN_OUT__

#include "../Base/Sprite.h"

class FadeIn_Out
{
	DX11::Sprite m_Sprite;
	bool SceneChangeFlag;
	int SceneChangeTime;
	bool In_OutFlag;
	int EndTime;
	bool EndFlag;
public:
	FadeIn_Out();
	void Init(bool In_Out, int End_Time);//In→0,Out→1 デフォルトでEndTimeは120
	void Init(bool In_Out, int End_Time, const std::string& filename);//In→0,Out→1 デフォルトでEndTimeは120
	void Begin(bool StartFlag);
	void End();//Begin関数のフラグがONになるとエフェクトを描画する関数
	bool Complete();
};

#endif