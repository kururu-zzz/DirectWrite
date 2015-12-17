#include "EffekseerManager.h"
#include "../../System/Base/Device.h"
#include "../../System/Base/Shader.h"

#if _DEBUG 
#pragma comment(lib, "Lib\\Debug\\Effekseer.lib" )
#pragma comment(lib, "Lib\\Debug\\EffekseerRendererDX11.lib" )
#else
#pragma comment(lib, "Lib\\Release\\Effekseer.lib" )
#pragma comment(lib, "Lib\\Release\\EffekseerRendererDX11.lib" )

#endif


void LoadEffect(
	const std::string& filename,
	std::unordered_map<std::string, std::shared_ptr<::Effekseer::Effect>>* effectMap,
	::Effekseer::Manager* manager
	)
{
	WCHAR	sNewPath[100];
	//�����R�[�h�ϊ�
	MultiByteToWideChar(CP_ACP, 0, filename.c_str(), -1, sNewPath, MAX_PATH);
	// �G�t�F�N�g�̓Ǎ�
	effectMap->emplace(filename, std::shared_ptr<::Effekseer::Effect>(
		Effekseer::Effect::Create(manager, (const EFK_CHAR*)sNewPath),
		[](::Effekseer::Effect* p)
	{
		p->Release();
	}));
}

void EffectCanvas::Init(ID3D11DeviceContext* deviceContext){

	// �`��p�C���X�^���X�̐���
	_renderer = std::shared_ptr<::EffekseerRenderer::Renderer>(::EffekseerRendererDX11::Renderer::Create(DX11::GetDevice(), deviceContext, 20000),
		[](::EffekseerRenderer::Renderer* p)
	{
		p->Destory();
	});

	// �G�t�F�N�g�Ǘ��p�C���X�^���X�̐���
	_manager = std::shared_ptr<::Effekseer::Manager>(::Effekseer::Manager::Create(20000),
		[](::Effekseer::Manager* p)
	{
		p->Destroy();
	});

	// �`��p�C���X�^���X����`��@�\��ݒ�
	_manager->SetSpriteRenderer(_renderer->CreateSpriteRenderer());
	_manager->SetRibbonRenderer(_renderer->CreateRibbonRenderer());
	_manager->SetRingRenderer(_renderer->CreateRingRenderer());
	_manager->SetModelRenderer(_renderer->CreateModelRenderer());
	_manager->SetTrackRenderer(_renderer->CreateTrackRenderer());

	// �`��p�C���X�^���X����e�N�X�`���̓Ǎ��@�\��ݒ�
	// �Ǝ��g���\�A���݂̓t�@�C������ǂݍ���ł���B
	_manager->SetTextureLoader(_renderer->CreateTextureLoader());
	_manager->SetModelLoader(_renderer->CreateModelLoader());

	_manager->SetCoordinateSystem(Effekseer::CoordinateSystem::LH);
}

bool EffectCanvas::BeginDrawEffect(const DX11::Camera& cam,ID3D11DeviceContext* deviceContext){ 

	DX11::GetShaderManager()->ResetShader(deviceContext);

	//_manager->Update();
	
	::Effekseer::Vector3D pos;
	::Effekseer::Vector3D foc;

	pos.X = cam.GetPos().x;
	pos.Y = cam.GetPos().y;
	pos.Z = cam.GetPos().z;

	foc.X = cam.GetFoc().x;
	foc.Y = cam.GetFoc().y;
	foc.Z = cam.GetFoc().z;
	
	// ���e�s���ݒ�
	_renderer->SetProjectionMatrix(
		::Effekseer::Matrix44().PerspectiveFovLH(45.f / 180.0f * 3.14f, 1200.f / 900.f, 10.0f, 15000.0f));

	// �J�����s���ݒ�
	_renderer->SetCameraMatrix(
		::Effekseer::Matrix44().LookAtLH(pos, foc, ::Effekseer::Vector3D(0.0f, 1.0f, 0.0f)));

	return _renderer->BeginRendering(); 
}

void EffectCanvas::DrawEffect(EffectObject* effect)
{
	auto effectName = effect->GetEffectName();
	if (_effectMap.find(effectName) == _effectMap.end())
		LoadEffect(effectName,&_effectMap,_manager.get());
	effect->Draw(_manager.get(), _effectMap.at(effectName).get());
}

bool EffectCanvas::EndDrawEffect(ID3D11DeviceContext* deviceContext)
{
	bool endRenderFlag = _renderer->EndRendering();
	DX11::GetShaderManager()->SetLayout(deviceContext);
	DX11::GetShaderManager()->ResetShader(deviceContext);
	return endRenderFlag;
}