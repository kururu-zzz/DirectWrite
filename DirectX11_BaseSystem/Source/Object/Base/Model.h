#ifndef __MODEL__
#define __MODEL__

#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <d3d11.h>

#include "Mesh.h"
#include "../../System/Loader/fbxResource.h"
#include "Material.h"
#include "Animation.h"

namespace DX11
{
	class Model{
	private:
		std::vector<std::shared_ptr<fbx::element::Mesh>> _meshContainer;
		std::vector<std::shared_ptr<fbx::element::Material>> _materialContainer;
		std::map<std::string, int> _meshIndexTable;
		std::unordered_map<std::string, int> _materialIndexTable;
		std::vector<std::shared_ptr<fbx::Animation>> _animContainer;
		std::unordered_map<std::string, int> _animIndexTable;
		std::string _currentAnimationName;
		std::unordered_map<int, DirectX::XMFLOAT4X4> _invBaseposeMatrixList;
		std::unordered_map<std::string, int> _boneNodeNameList;
		DirectX::XMFLOAT3 _pos;
		DirectX::XMFLOAT3 _angle;
	public:
		~Model();
		void Init(const DirectX::XMFLOAT3& pos, const std::string& modelname);
		void SetPos(const DirectX::XMFLOAT3& pos);
		void MovePos(const DirectX::XMFLOAT3& spd);
		void SetScale(const DirectX::XMFLOAT3& scale);
		void SetRotate(const DirectX::XMFLOAT3& angle);
		void SetRotate(const DirectX::XMFLOAT4X4& angle);

		std::shared_ptr<fbx::Animation> AccessAnimation(const std::string& animationName);
		std::shared_ptr<fbx::Animation> AccessAnimation(int animationIndex = 0);

		//all texture change
		void ChangeTexture(const std::string& fileName);

		void ApplyAnimation(const std::string& animationName);
		/*----------*/
		const DirectX::XMFLOAT3& GetPos(){ return _pos; }
		const DirectX::XMFLOAT3& GetRotate() { return _angle; }
		/*----------*/
		void Draw(ID3D11DeviceContext* deviceContext);
		void Draw(ID3D11DeviceContext* deviceContext,int InstanceNum);
	};
}

#endif