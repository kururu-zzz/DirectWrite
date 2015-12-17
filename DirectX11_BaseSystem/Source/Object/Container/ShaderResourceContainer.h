#ifndef _SHADERRESOURCECONTAINER
#define _SHADERRESOURCECONTAINER

#include <unordered_map>
#include <string>
#include <memory>
#include <d3d11.h>

class ShaderResourceContainer
{
private:
	std::unordered_map<std::string, std::shared_ptr<ID3D11ShaderResourceView>> _shaderResourceView;
	std::unordered_map<std::string, std::shared_ptr<ID3D11SamplerState>> _sampler;
private:
	ShaderResourceContainer(){}
	ShaderResourceContainer(const ShaderResourceContainer& rhs);
	ShaderResourceContainer& operator=(const ShaderResourceContainer& rhs);
public:
	static ShaderResourceContainer* GetInstance()
	{
		static ShaderResourceContainer msp_instance;
		return &msp_instance;
	}
	void CreateTexture(const std::string& fileName);
	void SetTexture(ID3D11DeviceContext* deviceContext, const std::string& fileName, int textureNum);
};

inline void SetTexture(ID3D11DeviceContext* deviceContext, const std::string& fileName, int slotNum = 0)
{
	return ShaderResourceContainer::GetInstance()->SetTexture(deviceContext,fileName,slotNum);
}

inline void CreateTexture(const std::string& fileName)
{
	ShaderResourceContainer::GetInstance()->CreateTexture(fileName);
}

#endif