#pragma comment(lib, "hkBase.lib")
#pragma comment(lib, "hkInternal.lib")
#pragma comment(lib, "hkpCollide.lib")
#pragma comment(lib, "hkpconstraintsolver.lib")
#pragma comment(lib, "hkpDynamics.lib")
#pragma comment(lib, "hkpinternal.lib")
#pragma comment(lib, "hkputilities.lib")

#include "Havok.h"

namespace havok
{	
	void OnError(const char* s, void* errorReportObject) {}
	
	void QuitHavok(hkMemoryRouter* p)
	{
		hkBaseSystem::quit();
		hkMemoryInitUtil::quit();
	}

	MainSystem::MainSystem() {
		auto memoryRouter = hkMemoryInitUtil::initDefault(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(500 * 1024));
		_memoryRouter = std::shared_ptr<hkMemoryRouter>(memoryRouter,QuitHavok);
		hkBaseSystem::init(_memoryRouter.get(), OnError);
	}
}