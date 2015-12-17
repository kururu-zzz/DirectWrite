#include "../../../header/System/Other/DebugFont.h"
#include "../../../header/System/Base/Shader.h"

#define WordSize 13.f
#define TabSize 400.f

HRESULT DebugFont::Init()
{
	const float WordNum = 95.f;
	state = State::SHOW;
	DebugFontPos = DebugWindowPos = XMFLOAT3((state == State::HIDE) * -TabSize,0.f,0.f);
	DebugWindowPos.z = 0.5f;
	m_Back.Init(DebugWindowPos, XMFLOAT2(TabSize, 900), XMFLOAT4(0.f, 0.f, 1.f, 1.f), "IMAGE\\BACK\\BLACKSCREEN.png");
	m_Back.SetAlpha(0.5f);
	for (int i = 0; i < WordNum; i++)
	{
		m_Word.push_back(std::make_shared<DX11::Sprite>());
		m_Word[i]->Init(XMFLOAT3((float)DebugFontPos.x, 0.f, 0.f), XMFLOAT2(WordSize, WordSize * 2), XMFLOAT4((float)i / WordNum, 0.f, (float)(i + 1) / WordNum, 1.0f), "IMAGE\\FONT\\DEBUGFONT.png");
	}
	return S_OK;
}

void DebugFont::TabIn(bool InFlag)
{
	if ((InFlag && (state == State::HIDE)) || (state == State::TABIN))
	{
		state = State::TABIN;
		DebugWindowPos.x += 10.0f;
		if (DebugWindowPos.x >= 0.f)
		{
			state = State::SHOW;
		}
	}
}

void DebugFont::TabOut(bool OutFlag)
{
	if ((OutFlag && (state == State::SHOW)) || (state == State::TABOUT))
	{
		state = State::TABOUT;
		DebugWindowPos.x -= 10.0f;
		if (DebugWindowPos.x <= -TabSize)
		{
			state = State::HIDE;
		}
	}
}

void DebugFont::SetMessage(const std::string& Message)
{
	MessageContainer.push_back(Message);
}

void DebugFont::Draw()
{
	/*
	if (state != State::HIDE)
	{
		m_Back.SetPos(DebugWindowPos);
		m_Back.Draw();
		DebugFontPos.y = 0.f;
		for (auto it = MessageContainer.begin(); it != MessageContainer.end(); ++it)
		{
			DebugFontPos.x = DebugWindowPos.x;
			for (int i = 0; (*it)[i] != NULL; i++)
			{
				m_Word[(*it)[i] - 32]->SetPos(DebugFontPos);
				m_Word[(*it)[i] - 32]->Draw();
				DebugFontPos.x += WordSize;
			}
			DebugFontPos.y += WordSize * 2;
		}
	}
	*/
}

void DebugFont::Draw(const std::string& Message,const XMFLOAT2& pos,const XMFLOAT2& Size)
{
	/*
	for (int i = 0; Message[i] != NULL; i++)
	{
		m_Word[Message[i] - 32]->Draw();
	}
	*/
}

void DebugFont::Destroy()
{

}