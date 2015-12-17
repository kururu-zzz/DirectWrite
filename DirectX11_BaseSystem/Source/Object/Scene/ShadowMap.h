#ifndef _SHADOWMAP
#define _SHADOWMAP

#include "../../System/Base/D3DX.h"
#include "../../System/Base/DXMath.h" 
using namespace DirectX;

class ShadowMap{
private:
	ID3D11Texture2D* m_pShadowMap; //�e�N�X�`��
	ID3D11RenderTargetView* m_pRTView; //�����_�[�^�[�Q�b�g�r���[
	ID3D11ShaderResourceView* m_pSRView; //�V�F�[�_�[���\�[�X�r���[
	ID3D11SamplerState *m_pSamDiffuse; //�T���v��
public:
	~ShadowMap();
	HRESULT Init(XMFLOAT2 Size);
	void SetRenderTarget();
	void SetTexture();
};

#endif