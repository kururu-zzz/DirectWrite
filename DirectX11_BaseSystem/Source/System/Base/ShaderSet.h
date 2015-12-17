#ifndef __SHADERID__
#define __SHADERID__

#include <d3d11.h>
#include <memory>
#include <string>

namespace DX11
{	
	struct ShaderSet
	{
		std::shared_ptr<ID3D11VertexShader> vs;
		std::shared_ptr<ID3D11GeometryShader> gs;
		std::shared_ptr<ID3D11PixelShader> ps;
		ShaderSet(){};
		ShaderSet(const std::string& keyName);
		ShaderSet(const std::string& keyName,
			const std::string& VSfuncName, const std::string& VSfileName,
			const std::string& GSfuncName, const std::string& GSfileName,
			const std::string& PSfuncName, const std::string& PSfileName);
		ShaderSet(const std::string& keyName,
			const std::string& VSfuncName, const std::string& GSfuncName,
			const std::string& PSfuncName, const std::string& fileName);
	};
}

#endif