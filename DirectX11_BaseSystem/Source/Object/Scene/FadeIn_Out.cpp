#include "../../../header/Object/Scene/FadeIn_Out.h"

FadeIn_Out::FadeIn_Out()
{
	m_Sprite.Init(XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT2(WINDOW_WIDTH, WINDOW_HEIGHT), XMFLOAT4(0.f, 0.f, 1.f, 1.f), "IMAGE\\BACK\\BLACKSCREEN.png");
	SceneChangeFlag = false;
	SceneChangeTime = 0;
	EndFlag = false;
	EndTime = 120;
	In_OutFlag = 1;
}

void FadeIn_Out::Init(bool In_Out, int End_Time)
{
	SceneChangeFlag = false;
	SceneChangeTime = 0;
	EndFlag = false;
	EndTime = End_Time;
	In_OutFlag = In_Out;
}

void FadeIn_Out::Init(bool In_Out, int End_Time, const std::string& filename)
{
	m_Sprite.ChangeImage(filename);
	SceneChangeFlag = false;
	SceneChangeTime = 0;
	EndFlag = false;
	EndTime = End_Time;
	In_OutFlag = In_Out;
}

void FadeIn_Out::Begin(bool StartFlag)
{
	if ((!SceneChangeFlag) && (!EndFlag)){
		SceneChangeFlag = StartFlag;
	}
}

void FadeIn_Out::End()
{
	if (!EndFlag)
	{
		if (In_OutFlag)
			m_Sprite.SetAlpha(SceneChangeTime / (float)EndTime);
		else
			m_Sprite.SetAlpha(1.0f - SceneChangeTime / (float)EndTime);
		if ((SceneChangeFlag) && (!EndFlag))
		{
			if (SceneChangeTime == EndTime)
				EndFlag = true;
			m_Sprite.Draw();
			SceneChangeTime++;
		}
	}
}

bool FadeIn_Out::Complete()
{
	return EndFlag;
}