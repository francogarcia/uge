/*
 * (c) Copyright 2013 - 2014 Franco Eusébio Garcia
 *
 * This file is part of UGE. 
 *
 * UGE is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser GPL v3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See 
 * http://www.gnu.org/licenses/lgpl-3.0.txt for more details.
 *
 * You should have received a copy of the GNU Lesser GPL v3
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 */

#pragma once

#include "GameEngineStd.h"

#include <new>

#if !defined(SAFE_DELETE)
/// Safely deletes a pointer, checking whether it's null before deleting.
#define SAFE_DELETE(p) if (p != nullptr) { delete p; p = nullptr; }
#endif

#if !defined(SAFE_DELETE_ARRAY)
/// Safely deletes an array, checking whether it's null before deleting.
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
