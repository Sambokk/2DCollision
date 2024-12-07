#pragma once


#include <windows.h>
#include <d2d1.h>
#include <d2d1_1.h>
#pragma comment(lib, "d2d1.lib")
//using D2D1::ColorF;

#include <dwrite.h>
#pragma comment(lib, "dwrite")

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <string>
using std::string;
using std::wstring;

#include  <utility>
using std::make_pair;
using std::pair;

#include <cassert>

#include <cmath>
#define _USE_MATH_DEFINES

#include <random>

#include <algorithm>

#include <limits>
using std::numeric_limits; //자료형의 최소 최대 값

#include <array>

#include <wincodec.h>
#pragma comment(lib, "windowscodecs")