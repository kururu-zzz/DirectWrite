#ifndef __EFFECT__
#define __EFFECT__

#include "Effekseer.h"
#include "EffekseerRendererDX11.h"
#include "EffectObject.h"
#include "../../System/Base/Camera.h"
#include <string>
#include <unordered_map>
#include <memory>

class EffectCanvas{
	std::shared_ptr<::EffekseerRenderer::Renderer> _renderer;
	std::shared_ptr<::Effekseer::Manager> _manager;
	std::unordered_map<std::string ,std::shared_ptr<::Effekseer::Effect>> _effectMap;
private:
	EffectCanvas(const EffectCanvas& rhs);
	EffectCanvas& operator=(const EffectCanvas& rhs);
public:
	EffectCanvas(){}
	void Init(ID3D11DeviceContext* deviceContext);
	bool BeginDrawEffect(const DX11::Camera& cam, ID3D11DeviceContext* deviceContext);
	void DrawEffect(EffectObject* effect);
	bool EndDrawEffect(ID3D11DeviceContext* deviceContext);

};

#endif