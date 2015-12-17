#ifndef __VIEWPORT__
#define __VIEWPORT__

#include "Camera.h"
#include "../../Object/Base/Light.h"
#include <vector>
#include <memory>

namespace DX11
{
	class Viewport{
	private:
		Camera _camera;
		std::vector<std::shared_ptr<Light>> _lights;
	public:
		Viewport(const DirectX::XMFLOAT2& size);
		Camera* GetCamera()
		{
			return &_camera;
		}
		Light* GetLight(const unsigned int lightId)
		{
			return _lights[lightId].get();
		}
	};
}
#endif