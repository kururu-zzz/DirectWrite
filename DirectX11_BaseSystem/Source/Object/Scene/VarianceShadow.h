#ifndef __VARIANCESHADOW__
#define __VARIANCESHADOW__

#include "../Base/Surface.h"
#include "../Base/Sprite.h"
#include "../../System/Base/DXMath.h"
#include "../../System/Base/Camera.h"
#include <array>

class VarianceShadowMap
{
private:
	std::array<DX11::Surface,2> _shadowMap;
public:
	HRESULT Init();
	DX11::Surface* GetShadowMap(){ return &_shadowMap[0]; }
	void BeginDrawDepthMap(ID3D11DeviceContext* deviceContext, DX11::Camera* cam, const DirectX::XMFLOAT3& lightPos);//深度バッファ書き込み開始、この後にモデル描画
	void EndDrawDepthMap(ID3D11DeviceContext* deviceContext,int blurNum,DX11::Surface* surface);//深度バッファのブラー処理およびテクスチャセット
};

#endif