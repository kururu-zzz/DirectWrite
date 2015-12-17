#ifndef __DXMATH__
#define __DXMATH__

#include <DirectXMath.h>

namespace DirectX
{
	inline XMFLOAT3 operator+ (const XMFLOAT3& f1, const XMFLOAT3& f2)
	{
		return XMFLOAT3(f1.x + f2.x, f1.y + f2.y, f1.z + f2.z);
	}

	inline XMFLOAT3 operator- (const XMFLOAT3& f1, const XMFLOAT3& f2)
	{
		return XMFLOAT3(f1.x - f2.x, f1.y - f2.y, f1.z - f2.z);
	}
	inline float CalcLength (const XMFLOAT3& f1, const XMFLOAT3& f2)
	{
		auto length = XMVector3Length(XMLoadFloat3(&f1) - XMLoadFloat3(&f2));
		return XMVectorGetX(length);
	}
	inline float CalcXZLength(const XMFLOAT3& f1, const XMFLOAT3& f2)
	{
		auto length = XMVector3Length(XMLoadFloat3(&XMFLOAT3(f1.x,0.f,f1.z)) - XMLoadFloat3(&XMFLOAT3(f2.x,0.f,f2.z)));
		return XMVectorGetX(length);
	}
}

#endif