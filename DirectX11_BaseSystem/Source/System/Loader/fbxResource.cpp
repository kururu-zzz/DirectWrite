#include "fbxResource.h"

#include <unordered_map>
#include <assert.h>
#include <future>

static std::mutex mutex;

#pragma comment( lib, "wininet.lib" )
#pragma comment( lib, "advapi32.lib" )
#if _DEBUG 
#pragma comment( lib, "libfbxsdk-md.lib" )
#else
#pragma comment( lib, "libfbxsdk-md.lib" )
#endif

namespace fbx
{
	namespace Resource
	{
		static std::unordered_map<std::string, std::shared_ptr<FbxScene>> sceneMap;
		std::shared_ptr<FbxScene> LoadModel(const std::string& fileName)
		{
			if (sceneMap.find(fileName) == sceneMap.end())
			{
				static std::shared_ptr<FbxManager> manager;
				if (manager == nullptr)
				{
					manager = std::shared_ptr<FbxManager>(FbxManager::Create(), [](FbxManager *p)
					{
						p->Destroy();
					});
					manager->SetIOSettings(FbxIOSettings::Create(manager.get(), IOSROOT));

					manager->LoadPluginsDirectory(FbxGetApplicationDirectory().Buffer(), "dll"); // windows‚Ì‚Ý‘Î‰ž
				}

				auto importer = std::shared_ptr<FbxImporter>(FbxImporter::Create(manager.get(), ""), [](FbxImporter* p)
				{
					p->Destroy();
				});
				if (!importer->Initialize(fileName.c_str(), -1, manager->GetIOSettings()))
					throw;

				auto _scene = FbxScene::Create(manager.get(), fileName.c_str());

				importer->Import(_scene);

				FbxGeometryConverter(manager.get()).Triangulate(_scene, true);
				sceneMap.emplace(fileName, std::shared_ptr<FbxScene>(_scene, [](FbxScene *p)
				{
					//p->Destroy();
				}));
			}
			return sceneMap.at(fileName);
		}
		void ClearResource()
		{
			sceneMap.clear();
		}
	}
}