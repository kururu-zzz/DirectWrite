#ifndef _SPRITE
#define _SPRITE

#include <array>
#include <string>
#include <d3d11.h>
#include <memory>

#include "VertexData.h"

namespace DX11
{
	class Sprite{
	private:
		DirectX::XMFLOAT3 _pos;
		DirectX::XMFLOAT2 _size;
		DirectX::XMFLOAT2 _base;
		DirectX::XMFLOAT3X3 matRotate;
		float _degree;
		std::array<Vertex::DefaultVertex, 4> pV;
		std::string _fileName;
	public:
		Sprite();
		void Init(const DirectX::XMFLOAT3& pos, const DirectX::XMFLOAT2& size, const DirectX::XMFLOAT4& texel, const std::string& fileName);
		void Draw(ID3D11DeviceContext* deviceContext);
		/*---------------*/

		void SetTexel(const DirectX::XMFLOAT4& texel);
		void SetPos(const DirectX::XMFLOAT3& pos);
		void MovePos(const DirectX::XMFLOAT3& spd);
		void SetSize(const DirectX::XMFLOAT2& size);
		void SetSizeFromCenter(const DirectX::XMFLOAT2& size);
		void SetBase(const DirectX::XMFLOAT2& base);
		void SetRotate(const float degree);
		void SetRotateFromCenter(const float degree);
		void SetAlpha(float alpha);

		void ChangeImage(const std::string& fileName);

		float GetAlpha();

		const DirectX::XMFLOAT3& GetPos(){ return _pos; }
	};
}
#endif