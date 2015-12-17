#include "../../../header/Object/Scene/ShadowMap.h"
#include "../../../header/System/Matrix/ConstantBufferManager.h"

HRESULT ShadowMap::Init(XMFLOAT2 size)
{
	
	// レンダリングテクスチャを作成する
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = (UINT)size.x;
	desc.Height = (UINT)size.y;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R16G16_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	//修正
	//SetScSize(XMFLOAT2(WINDOW_WIDTH, WINDOW_HEIGHT));

	if(FAILED(GetD3D()->GetDevice()->CreateTexture2D(&desc, NULL, &m_pShadowMap)))
		throw;

	// レンダリングターゲットを作成する
	if(FAILED(GetD3D()->GetDevice()->CreateRenderTargetView(m_pShadowMap, NULL, &m_pRTView)))
		throw;

	// ShaderResourceViewを作成する
	// これを作成しておかないとテクスチャリソースとして使用できない
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R16G16_UNORM;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip = 0;
	srvDesc.Texture2D.MipLevels = desc.MipLevels;

	if(FAILED(GetD3D()->GetDevice()->CreateShaderResourceView(m_pShadowMap, &srvDesc, &m_pSRView)))
		throw;

	// サンプラを作成する
	D3D11_SAMPLER_DESC samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	samDesc.AddressU = samDesc.AddressV = samDesc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	samDesc.BorderColor[0] = samDesc.BorderColor[1] = samDesc.BorderColor[2] = samDesc.BorderColor[3] = static_cast<float>(0xFFFFFFFF);
	samDesc.MipLODBias = 0.f;
	samDesc.MaxAnisotropy = 0;
	samDesc.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	samDesc.MinLOD = 0;
	samDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if(FAILED(GetD3D()->GetDevice()->CreateSamplerState(&samDesc, &m_pSamDiffuse)))
		throw;
	
	return S_OK;
}

void ShadowMap::SetRenderTarget()
{
	GetD3D()->GetContext()->OMSetRenderTargets(1, &m_pRTView, NULL);
	float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GetD3D()->GetContext()->ClearRenderTargetView(m_pRTView, clearColor);
}

void ShadowMap::SetTexture()
{
	GetD3D()->Begin();
	GetD3D()->GetContext()->PSSetShaderResources(5, 1, &m_pSRView);
	GetD3D()->GetContext()->PSSetSamplers(5, 1, &m_pSamDiffuse);
}

ShadowMap::~ShadowMap()
{
	SAFE_RELEASE(m_pShadowMap);
	SAFE_RELEASE(m_pSRView);
	SAFE_RELEASE(m_pSamDiffuse);
	SAFE_RELEASE(m_pRTView);
}