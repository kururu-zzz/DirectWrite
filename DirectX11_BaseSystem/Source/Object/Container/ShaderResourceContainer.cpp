#include "ShaderResourceContainer.h"
#include "../../System/Base/DXResource.h"
#include <mutex>

static std::mutex mutex;

void ShaderResourceContainer::CreateTexture(const std::string& fileName)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (_shaderResourceView.find(fileName) == _shaderResourceView.end() && fileName != "")
	{
		_shaderResourceView.emplace(fileName, DX11::Resource::CreateShaderResourceView(fileName));

		_sampler.emplace(fileName, DX11::Resource::CreateSampler());
	}
}

void ShaderResourceContainer::SetTexture(ID3D11DeviceContext* deviceContext, const std::string& fileName, int textureNum)
{
	std::lock_guard<std::mutex> lock(mutex);
	if (_shaderResourceView.find(fileName) != _shaderResourceView.end())
	{
		ID3D11ShaderResourceView* shaderResourceView = _shaderResourceView.at(fileName).get();
		ID3D11SamplerState* sampler = _sampler.at(fileName).get();

		deviceContext->PSSetShaderResources(textureNum, 1, &shaderResourceView);
		deviceContext->PSSetSamplers(textureNum, 1, &sampler);
	}
}