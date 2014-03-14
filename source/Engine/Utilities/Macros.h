#pragma once

#include "GameEngineStd.h"

#include <new>

#if !defined(SAFE_DELETE)
/// Safely deletes a pointer, checking if whether it's null before deleting.
#define SAFE_DELETE(p) if (p != nullptr) { delete p; p = nullptr; }
#endif

#if !defined(SAFE_DELETE_ARRAY)
/// Safely deletes an array, checking if whether it's null before deleting.
#define SAFE_DELETE_ARRAY(pArray) if (pArray != nullptr) { delete[] pArray; pArray = nullptr; }
#endif

// Redefines NEW to check for memory leak in Debug Mode.
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW

#include <stdlib.h>
#include <crtdbg.h>

#define LIB_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define LIB_NEW new
#endif
