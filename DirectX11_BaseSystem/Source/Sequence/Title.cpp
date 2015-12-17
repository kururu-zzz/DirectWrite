#include "Title.h"
#include "../System/Matrix/ConstantBufferManager.h"
#include "../System/Base/DXInput.h"
#include "../System/Base/DXMath.h"
#include "../System/Base/Music.h"
#include "../System/Base/Joypad.h"
#include <future>

using namespace DirectX;
static std::mutex mutex;

Title::Title() : Sequence(typeid(this).name())
{
}

void Title::Init(const std::string& beforeSequenceName){
	_priority = 1;

	_state = State::updatable;
}

bool Title::Update(std::unordered_map<std::string, std::shared_ptr<Sequence>>* sequenceContainer)
{
	_state = State::active;
	return true;
}

void Title::Draw(DX11::Canvas* canvas)
{
	canvas->GetCamera(0)->SetPos(XMFLOAT3(0.f, 0.f, 50.f));
	canvas->SetCameraBuffer();
	//canvas->SetRenderTarget(&_surface);
	canvas->SetDefaultRenderTarget();

	canvas->DrawText(L"•¶Žš—ñ•`‰æ");

	//canvas->SetConstantBuffer(XMFLOAT4(_time, _oldTime, 0.f, 0.f), DX11::ConstantBuffer::cBufferSlot::Variable);
	//canvas->DrawSurface(&_surface, _surface.GetShader());
}

