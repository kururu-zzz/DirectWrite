#include "Sprite.h"
#include "../../System/Matrix/ConstantBufferManager.h"
#include "../Container/ShaderResourceContainer.h"
#include "../../System/Base/Shader.h"

using namespace DirectX;

namespace DX11
{
	static std::shared_ptr<ID3D11Buffer> vb;

	void SetVertexPos(std::array<Vertex::DefaultVertex,4>& v,XMFLOAT3 pos,XMFLOAT2 base,XMFLOAT2 size,float degree)
	{
		v[0].pos = XMFLOAT3(pos.x, pos.y , pos.z);
		v[1].pos = XMFLOAT3(pos.x + size.x, pos.y, pos.z);
		v[2].pos = XMFLOAT3(pos.x, pos.y + size.y, pos.z);
		v[3].pos = XMFLOAT3(pos.x + size.x, pos.y + size.y, pos.z);
		std::for_each(v.begin(), v.end(), [base](Vertex::DefaultVertex& p)
		{
			p.pos = p.pos - XMFLOAT3(base.x, base.y, 0.f);
		});
		XMFLOAT3X3 matRotate;
		XMStoreFloat3x3(&matRotate, XMMatrixIdentity());
		float rad = XMConvertToRadians(degree);
		matRotate._11 = matRotate._22 = cosf(rad);
		matRotate._12 = sinf(rad);
		matRotate._21 = -sinf(rad);
		std::for_each(v.begin(), v.end(), [base, matRotate](Vertex::DefaultVertex& p)
		{
			XMStoreFloat3(&p.pos, XMVector3Transform(XMLoadFloat3(&p.pos), XMLoadFloat3x3(&matRotate)));
			p.pos = p.pos + XMFLOAT3(base.x, base.y, 0.f);
		});
	}

	void UpdateVertex(Vertex::DefaultVertex* v, ID3D11DeviceContext* deviceContext)
	{
		D3D11_MAPPED_SUBRESOURCE resource;
		auto hr = deviceContext->Map(vb.get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource);
		if (SUCCEEDED(hr)) {
			auto param = (Vertex::DefaultVertex*)(resource.pData);
			for (int i = 0; i < 4; ++i)
			{
				param[i] = v[i];
			}
			deviceContext->Unmap(vb.get(), 0);
		}
	}

	Sprite::Sprite()
	{
		if (vb == nullptr)
		{
			std::array<Vertex::DefaultVertex, 4> vertex;
			ID3D11Buffer* vbuf;
			auto hr = CreateBuffer(&vbuf, (void*)vertex.data(), sizeof(Vertex::DefaultVertex)* vertex.size(), D3D11_CPU_ACCESS_WRITE, D3D11_BIND_VERTEX_BUFFER);
			assert(SUCCEEDED(hr));
			vb = std::shared_ptr<ID3D11Buffer>(vbuf, [](ID3D11Buffer* p)
			{
				p->Release();
			});
		}
	}

	void Sprite::Init(const XMFLOAT3& pos, const XMFLOAT2& size, const XMFLOAT4& texel, const std::string& fileName)
	{
		_fileName = fileName;
		CreateTexture(_fileName);

		_pos = pos;
		_size = size;

		_degree = 0.f;

		if (_pos.z >= 1.0f)
			_pos.z = 0.99999f;

		pV[0].color = pV[1].color = pV[2].color = pV[3].color = 0xff000000;

		_base = XMFLOAT2(size.x / 2.f, size.y / 2.f);

		XMFLOAT3 faceEdgeA = pV[1].pos - pV[0].pos;
		XMFLOAT3 faceEdgeB = pV[2].pos - pV[0].pos;

		XMFLOAT3 faceNormal;
		XMStoreFloat3(&faceNormal, XMVector3Normalize(XMVector3Cross(XMLoadFloat3(&faceEdgeA), XMLoadFloat3(&faceEdgeB))));

		pV[0].normal = pV[1].normal = pV[2].normal = pV[3].normal = faceNormal;

		pV[0].texel = XMFLOAT2(texel.x, texel.y);
		pV[1].texel = XMFLOAT2(texel.z, texel.y);
		pV[2].texel = XMFLOAT2(texel.x, texel.w);
		pV[3].texel = XMFLOAT2(texel.z, texel.w);
	}

	void Sprite::ChangeImage(const std::string& fileName)
	{
		_fileName = fileName;
		CreateTexture(_fileName);
	}

	void Sprite::SetTexel(const XMFLOAT4& texel){
		pV[0].texel = XMFLOAT2(texel.x, texel.y);
		pV[1].texel = XMFLOAT2(texel.z, texel.y);
		pV[2].texel = XMFLOAT2(texel.x, texel.w);
		pV[3].texel = XMFLOAT2(texel.z, texel.w);
	}

	void Sprite::MovePos(const XMFLOAT3& spd)
	{
		_pos = _pos + spd;
	}

	void Sprite::SetBase(const XMFLOAT2& base)
	{
		_base = base;
	}

	void Sprite::SetRotate(const float degree)
	{
		_degree = degree;
	}

	void Sprite::SetRotateFromCenter(const float degree)
	{
		_degree = degree;
		_base = XMFLOAT2(_pos.x + _size.x / 2, _pos.y + _size.y/2);
	}

	void Sprite::SetPos(const XMFLOAT3& pos){
		_pos = pos;
		if (_pos.z >= 1.0f)
			_pos.z = 0.99999f;
	}

	//画像の中心からのサイズ変更
	void Sprite::SetSizeFromCenter(const XMFLOAT2& size){
		XMFLOAT2 difference = XMFLOAT2((size.x - _size.x) / 2.f, (size.y - _size.y) / 2.f);
		_pos = XMFLOAT3(_pos.x - difference.x, _pos.y - difference.y, _pos.z);
		_size = size;
	}

	void Sprite::SetAlpha(float alpha){
		std::for_each(pV.begin(), pV.end(), [alpha](Vertex::DefaultVertex& v)
		{
			if (alpha <= 0.f)
			{
				v.color = (uint32_t)(0xff000000 * 0.f);
			}
			else if (alpha >= 1.f)
			{
				v.color = (uint32_t)(0xff000000 * 1.f);
			}
			else
			{
				v.color = (uint32_t)(0xff000000 * alpha);
			}
		});
	}

	float Sprite::GetAlpha(){
		return (float)(pV[0].color / (uint32_t)0xff000000);
	}

	void Sprite::SetSize(const XMFLOAT2& size){
		_size = size;
	}

	void Sprite::Draw(ID3D11DeviceContext* deviceContext){
		SetVertexPos(pV, _pos, _base,_size, _degree);
		UpdateVertex(pV.data(), deviceContext);
		SetTexture(deviceContext,_fileName);
		
		UINT SizeTbl[] = { sizeof(Vertex::DefaultVertex) };
		UINT OffsetTbl[] = { 0 };
		ID3D11Buffer* pBufferTbl[] = { vb.get() };
		deviceContext->IASetVertexBuffers(0, 1, pBufferTbl, SizeTbl, OffsetTbl);

		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		deviceContext->Draw(4, 0);
	}
}
