#ifndef _FEEDBACK
#define _FEEDBACK

#include "../Base/Surface.h"
#include "../Base/Sprite.h"

class FeedBack
{
private:
	Surface m_Surface[2];
	DX11::Sprite m_Sprite;
	bool SceneChangeFlag;
	int SceneChangeTime;
	bool EndFlag;
public:
	FeedBack();
	void Begin(bool StartFlag);
	void End();//Begin�֐��̃t���O��ON�ɂȂ�ƃG�t�F�N�g��`�悷��֐�
	bool Complete();
};

#endif