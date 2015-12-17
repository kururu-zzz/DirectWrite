#include "Shader.h"
#include "DXResource.h"

namespace DX11
{
	ShaderSet::ShaderSet(const std::string& keyName)
	{
		vs = GetShaderManager()->CreateVertexShader(keyName, "", "");
		gs = GetShaderManager()->CreateGeometryShader(keyName, "", "");
		ps = GetShaderManager()->CreatePixelShader(keyName, "", "");
	}
	ShaderSet::ShaderSet(const std::string& keyName,
		const std::string& VSfuncName, const std::string& GSfuncName,
		const std::string& PSfuncName, const std::string& fileName)
	{
		vs = GetShaderManager()->CreateVertexShader(keyName, VSfuncName, fileName);
		gs = GetShaderManager()->CreateGeometryShader(keyName, GSfuncName, fileName);
		ps = GetShaderManager()->CreatePixelShader(keyName, PSfuncName, fileName);
	}
	ShaderSet::ShaderSet(const std::string& keyName,
		const std::string& VSfuncName, const std::string& VSfileName,
		const std::string& GSfuncName, const std::string& GSfileName,
		const std::string& PSfuncName, const std::string& PSfileName)
	{
		vs = GetShaderManager()->CreateVertexShader(keyName, VSfuncName, VSfileName);
		gs = GetShaderManager()->CreateGeometryShader(keyName, GSfuncName, GSfileName);
		ps = GetShaderManager()->CreatePixelShader(keyName, PSfuncName, PSfileName);
	}
	const std::shared_ptr<ID3D11VertexShader>& ShaderManager::CreateVertexShader(const std::string& keyname, const std::string& functionName, const std::string& fileName)
	{
		if (VSContainer.find(keyname) == VSContainer.end())
		{
			_vertexBlob = Resource::CompileShaderFromFile(fileName, functionName, "vs_4_0");
			VSContainer.emplace(um_VS::value_type(keyname,
				Resource::CreateVertexShader(_vertexBlob.get())));
		}
		return VSContainer[keyname];
	}
	const std::shared_ptr<ID3D11GeometryShader>& ShaderManager::CreateGeometryShader(const std::string& keyname, const std::string& functionName, const std::string& fileName)
	{
		if (GSContainer.find(keyname) == GSContainer.end())
		{
			GSContainer.emplace(um_GS::value_type(keyname,
				Resource::CreateGeometryShader(Resource::CompileShaderFromFile(fileName, functionName, "gs_4_0").get())));
		}
		return GSContainer[keyname];
	}
	const std::shared_ptr<ID3D11PixelShader>& ShaderManager::CreatePixelShader(const std::string& keyname, const std::string& functionName, const std::string& fileName)
	{
		if (PSContainer.find(keyname) == PSContainer.end())
		{
			PSContainer.emplace(um_PS::value_type(keyname,
				Resource::CreatePixelShader(Resource::CompileShaderFromFile(fileName, functionName, "ps_4_0").get())));
		}
		return PSContainer[keyname];
	}
	void ShaderManager::SetLayout(ID3D11DeviceContext* deviceContext){
		if (_layout == nullptr)
		{
			if (_vertexBlob == nullptr)
			{
				return;
			}
			_layout = Resource::CreateLayout(_vertexBlob.get());
		}
		deviceContext->IASetInputLayout(_layout.get());
	}
	void ShaderManager::SetShader(ID3D11DeviceContext* deviceContext, const ShaderSet& shaderSet){

		// ShaderManagerのセットアップ
		deviceContext->VSSetShader(shaderSet.vs.get(), 0, 0);

		deviceContext->GSSetShader(shaderSet.gs.get(), 0, 0);

		deviceContext->PSSetShader(shaderSet.ps.get(), 0, 0);

	}
	void ShaderManager::ResetShader(ID3D11DeviceContext* deviceContext){
		// ShaderManagerのセットアップ
		deviceContext->VSSetShader(nullptr, nullptr, 0);

		deviceContext->GSSetShader(nullptr, nullptr, 0);

		deviceContext->PSSetShader(nullptr, nullptr, 0);
	}
}