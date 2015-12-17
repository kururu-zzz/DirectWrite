#pragma once

#include <Windows.h>
#include <tchar.h>
#include <time.h>
#include <string>
#include <assert.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <array>

#define WINDOW_WIDTH 1200.f
#define WINDOW_HEIGHT 900.f

#define	SAFE_DELETE(p) { if(p){ delete p; p=NULL; } }
#define	SAFE_DELETEARRAY(p) { if(p){ delete [] p; p=NULL;} }
#define	SAFE_RELEASE(p) { if(p){ p->Release(); p=NULL;} }
