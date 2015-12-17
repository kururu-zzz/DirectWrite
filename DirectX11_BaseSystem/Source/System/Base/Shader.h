#ifndef __SHADER__
#define __SHADER__

#include "ShaderSet.h"

#include <d3d11.h>
#include <unordered_map>
#include <memory>
#include <string>

/**
*@brief シェーダー管理クラス
*
*シングルトン
*/
namespace DX11
{
	class ShaderManager{
		using um_VS = std::unordered_map<std::string, std::shared_ptr<ID3D11VertexShader>>;
		using um_GS = std::unordered_map<std::string, std::shared_ptr<ID3D11GeometryShader>>;
		using um_PS = std::unordered_map<std::string, std::shared_ptr<ID3D11PixelShader>>;
	protected:
		um_VS VSContainer; ///< 頂点シェーダー
		um_GS GSContainer; ///< ジオメトリシェーダー
		um_PS PSContainer; ///< ピクセルシェーダー
		std::shared_ptr<ID3DBlob> _vertexBlob; ///< 入力レイアウト
		std::shared_ptr<ID3D11InputLayout> _layout; ///< 入力レイアウト
	private:
		ShaderManager(){}
		ShaderManager(const ShaderManager& rhs);
		ShaderManager& operator=(const ShaderManager& rhs);

	public:
		static ShaderManager* GetInstance(){
			static ShaderManager msp_instance;
			return &msp_instance;
		}
		const std::shared_ptr<ID3D11VertexShader>& CreateVertexShader(const std::string& keyname, const std::string& functionName, const std::string& fileName);
		const std::shared_ptr<ID3D11GeometryShader>& CreateGeometryShader(const std::string& keyname, const std::string& functionName, const std::string& fileName);
		const std::shared_ptr<ID3D11PixelShader>& CreatePixelShader(const std::string& keyname, const std::string& functionName, const std::string& fileName);
		void SetShader(ID3D11DeviceContext* deviceContext, const ShaderSet& shaderSet);///< シェーダーセット関数
		void ResetShader(ID3D11DeviceContext* deviceContext);///< シェーダーリセット関数
		void SetLayout(ID3D11DeviceContext* deviceContext);///< レイアウトセット関数
	};

	inline ShaderManager* GetShaderManager(){
		return ShaderManager::GetInstance();
	}
}

#endif