#include "Viewport.h"

using namespace DirectX;

namespace DX11
{
	Viewport::Viewport(const XMFLOAT2& size)
	{
		_camera.Init(XMFLOAT3(0.f, 0.f, -50.f), XMFLOAT3(0.f, 0.f, 0.f), size);
		_lights.emplace_back(std::make_shared<Light>());
		_lights[0]->SetPos(XMFLOAT3(0.f, 5000.f, 0.f));
	}
}