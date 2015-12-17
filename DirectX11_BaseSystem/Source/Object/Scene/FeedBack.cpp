#include "../../../header/Object/Scene/FeedBack.h"
#include "../../../header/System/Base/Shader.h"

FeedBack::FeedBack()
{
	m_Surface[0].Init(XMFLOAT2(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_Surface[1].Init(XMFLOAT2(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_Sprite.Init(XMFLOAT3(0.f, 0.f, 0.f), XMFLOAT2(WINDOW_WIDTH, WINDOW_HEIGHT), XMFLOAT4(0.f, 0.f, 1.f, 1.f), "Surface");
	SceneChangeFlag = false;
	SceneChangeTime = 0;
	EndFlag = false;
}

void FeedBack::Begin(bool StartFlag)
{
	if (!SceneChangeFlag){
		SceneChangeFlag = StartFlag;
		if (SceneChangeFlag)
		{
			m_Surface[0].SetRenderTarget();
			SceneChangeTime++;
		}
	}
}

void FeedBack::End()
{
	if ((SceneChangeFlag) && (!EndFlag))
	{
		m_Surface[(SceneChangeTime - 1) % 2].SetTexture();
		m_Surface[SceneChangeTime % 2].SetRenderTarget();
		//GetShader()->SetShader(SI_FeedBack);
		m_Sprite.Draw();
		m_Surface[SceneChangeTime % 2].SetTexture();
		GetShader()->SetShader(ShaderName::Surface);
		m_Sprite.Draw();
		SceneChangeTime++;
		if (SceneChangeTime == 120)
			EndFlag = true;
	}
}

bool FeedBack::Complete()
{
	return EndFlag;
}