#ifndef __FBXRESOURCE__
#define __FBXRESOURcE__

#include <string>
#include <fbxsdk.h>
#include <memory>

namespace fbx
{
	namespace Resource
	{
		std::shared_ptr<FbxScene> LoadModel(const std::string& fileName);
		void ClearResource();
	}
};

#endif