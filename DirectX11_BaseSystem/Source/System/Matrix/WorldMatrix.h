#ifndef __W_MATRIX__
#define __W_MATRIX__

#include "../Base/DXMath.h" 
#include <d3d11.h>
#include <vector>

namespace DX11
{
	namespace ConstantBuffer
	{
		struct cWorldBuffer
		{
			DirectX::XMFLOAT4X4	matWorld;
			cWorldBuffer()
			{
				DirectX::XMStoreFloat4x4(&matWorld, DirectX::XMMatrixIdentity());
			}
		};
	}

	class WorldMatrix{//�p���O��
	protected:
		WorldMatrix();
		virtual ~WorldMatrix();
		ConstantBuffer::cWorldBuffer _worldBuf;
		DirectX::XMFLOAT3 _scale, _translate;
		DirectX::XMFLOAT4X4 _rotate; //��]�D�揇���̖��̓s����
		void SetWorldBuffer(ID3D11DeviceContext* deviceContext);//�`��O�ɌĂяo���B
		void SetPos(const DirectX::XMFLOAT3& pos);
		void SetScale(const DirectX::XMFLOAT3& pos);
		void SetRotate(const DirectX::XMFLOAT3& angle);
		void SetRotate(const DirectX::XMFLOAT4X4& angle);
	};
}
#endif