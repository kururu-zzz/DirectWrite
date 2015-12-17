#ifndef __SHADER__
#define __SHADER__

#include "ShaderSet.h"

#include <d3d11.h>
#include <unordered_map>
#include <memory>
#include <string>

/**
*@brief �V�F�[�_�[�Ǘ��N���X
*
*�V���O���g��
*/
namespace DX11
{
	class ShaderManager{
		using um_VS = std::unordered_map<std::string, std::shared_ptr<ID3D11VertexShader>>;
		using um_GS = std::unordered_map<std::string, std::shared_ptr<ID3D11GeometryShader>>;
		using um_PS = std::unordered_map<std::string, std::shared_ptr<ID3D11PixelShader>>;
	protected:
		um_VS VSContainer; ///< ���_�V�F�[�_�[
		um_GS GSContainer; ///< �W�I���g���V�F�[�_�[
		um_PS PSContainer; ///< �s�N�Z���V�F�[�_�[
		std::shared_ptr<ID3DBlob> _vertexBlob; ///< ���̓��C�A�E�g
		std::shared_ptr<ID3D11InputLayout> _layout; ///< ���̓��C�A�E�g
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
		void SetShader(ID3D11DeviceContext* deviceContext, const ShaderSet& shaderSet);///< �V�F�[�_�[�Z�b�g�֐�
		void ResetShader(ID3D11DeviceContext* deviceContext);///< �V�F�[�_�[���Z�b�g�֐�
		void SetLayout(ID3D11DeviceContext* deviceContext);///< ���C�A�E�g�Z�b�g�֐�
	};

	inline ShaderManager* GetShaderManager(){
		return ShaderManager::GetInstance();
	}
}

#endif