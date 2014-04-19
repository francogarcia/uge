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

#include <stdio.h>

#pragma message ("GAME ENGINE STD: " \
                 "Using the precompiled header")

// C++ Standard Library and STL
#include <algorithm>
#include <array>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <strstream>
#include <vector>

// C++11 Standard Library
#include <chrono>
#include <codecvt>
#include <functional>
#include <locale>
#include <mutex>
#include <thread>
#include <memory>
#include <regex>

// OpenGL Math Library
// Makes GLM use radians instead as degrees.
#define GLM_FORCE_RADIANS 
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// Bullet Physics Library
#include <btBulletDynamicsCommon.h>
#include <btBulletCollisionCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

// OIS
#define OIS_DYNAMIC_LIB
#include <OIS/OIS.h>

// Ogre 3D
#include <OGRE/Ogre.h>
#include <OGRE/OgreFrameListener.h>
// OgreOggSound
//#include <OgreOggSoundManager.h>

// YSE
#include <yse.hpp>

// OpenAL Soft
//#include <AL/al.h>
//#include <AL/alc.h>
//#include <AL/alext.h>
//

// TinyOAL
#include <cTinyOAL.h>

// LuaPlus
#include <LuaPlus/LuaPlus.h>

// TinyXML 2
#include <tinyxml2.h>

// Hyperic Sigar
#include <sigar.h>

// PhysFS
#include <physfs.h>

// Fast Delegate
// TODO: change fast delegate to std::function if possible.
#include <FastDelegate.h>
#include <FastDelegateBind.h>

// Defines some useful macros.
#include <Utilities/Macros.h>
// Define cross-platform primitive types.
#include <Utilities/Types.h>

// Disable VS warning C4482, regarding enum usage.
#pragma warning(disable: 4482)
// Disable VS warning LNK4221 and LNK4006, regarding linkage.
//#pragma warning(disable: 4221)
//#pragma warning(disable: 4006)


