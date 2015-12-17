#ifndef __DEBUGFONT__
#define __DEBUGFONT__

#include "../../Object/Base/Sprite.h"
#include <vector>

class DebugFont
{
private:
	enum State
	{
		HIDE,
		SHOW,
		TABIN,
		TABOUT,
	};

private:
	DebugFont(){}
	DebugFont(const DebugFont& rhs);
	DebugFont& operator=(const DebugFont& rhs);
public:
	static DebugFont* GetInstance(){
		static DebugFont msp_instance;
		return &msp_instance;
	}
private:
	XMFLOAT3 DebugWindowPos,DebugFontPos;
	std::vector<DX11::s_Sprite> m_Word;
	std::vector<std::string> MessageContainer;
	DX11::Sprite m_Back;
	State state;
public:
	HRESULT Init();
	void SetMessage(const std::string& Message);
	void Update();
	void TabIn(bool InFlag);
	void TabOut(bool OutFlag);
	void Draw();
	void Draw(const std::string& Message, const XMFLOAT2& pos, const XMFLOAT2& Size);
	void Destroy();
};

inline DebugFont* GetDebugFont()
{
	return DebugFont::GetInstance();
}

inline void DrawDebugFont()
{
	DebugFont::GetInstance()->Draw();
}

inline void DrawFreeFont(const std::string& Message, const XMFLOAT2& pos, const XMFLOAT2& Size)
{
	DebugFont::GetInstance()->Draw(Message, pos, Size);
}

inline void SetMessage(const std::string& Message)
{
	DebugFont::GetInstance()->SetMessage(Message);
}

inline void FontTabIn(bool InFlag)
{
	DebugFont::GetInstance()->TabIn(InFlag);
}

inline void FontTabOut(bool OutFlag)
{
	DebugFont::GetInstance()->TabOut(OutFlag);
}
#endif