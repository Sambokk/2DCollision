#include "pch.h"
#include "DRD2DEngine.h"
#include "DRMacro.h"

#include "Object.h"
#include "GameEngine.h"
#include "SceneManager.h"
#include "Scene.h"

#include "CollisionManager.h"
#include "TimeManager.h"
#include "MouseManager.h"

DRD2DEngine::DRD2DEngine()
	: hWnd(NULL), direct2DFactory(nullptr),
	renderTarget(nullptr), gameEngine(nullptr),
	defaultTextFormat(nullptr), writeFactory(nullptr)
{
}

DRD2DEngine::~DRD2DEngine()
{
	SafeRelease(&direct2DFactory);
	SafeRelease(&writeFactory);
}

void DRD2DEngine::Initialize(HWND _hWnd, GameEngine* _gameEngine)
{
	hWnd = _hWnd;
	gameEngine = _gameEngine;

	// 1. Direct2D Factory를 만든다.
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &direct2DFactory);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory),
		reinterpret_cast<IUnknown**>(&writeFactory));

	//디폴트 텍스트 포멧을 만든다
	writeFactory->CreateTextFormat(
		L"Tahoma",					 // 폰트 패밀리 이름의 문자열
		NULL,                        // 폰트 컬렉션 객체, NULL=시스템 폰트 컬렉션
		DWRITE_FONT_WEIGHT_NORMAL,   // 폰트 굵기. LIGHT, NORMAL, BOLD 등.
		DWRITE_FONT_STYLE_NORMAL,    // 폰트 스타일. NORMAL, OBLIQUE, ITALIC.
		DWRITE_FONT_STRETCH_NORMAL,  // 폰트 간격. CONDENSED, NORMAL, MEDIUM, EXTEXDED 등.
		20,                          // 폰트 크기.
		L"ko-kr",                    // 로케일을 문자열로 명시.  영어-미국=L"en-us", 한국어-한국=L"ko-kr"
		&defaultTextFormat
	);

	CreateDeviceResources();
	CreateBrushes();
}

HRESULT DRD2DEngine::CreateDeviceResources()
{
	HRESULT hr = S_OK;

	// 2. Create a Direct2D render target.
	if (renderTarget == nullptr)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U m_size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top);

		hr = direct2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, m_size,D2D1_PRESENT_OPTIONS_IMMEDIATELY),
			&renderTarget);
	}

	return hr;
}


void DRD2DEngine::Loop()
{

}

void DRD2DEngine::Render()
{
	HRESULT hr = CreateDeviceResources();

	if (SUCCEEDED(hr) && !(renderTarget->CheckWindowState() & D2D1_WINDOW_STATE_OCCLUDED))
	{
		// Retrieve the m_size of the render target.
		D2D1_SIZE_F renderTargetSize = renderTarget->GetSize();

		renderTarget->BeginDraw();

		renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

		// Apply the translation transform to the render target.
		//renderTarget->SetTransform(D2D1::Matrix3x2F::Translation(WINDOW_WIDTH/2, WINDOW_HEIGHT/2));


		ObjectRender();
		ManagerRender();

		hr = renderTarget->EndDraw();
	}
}

bool sortLayer(Object* obj1, Object* obj2)
{
	if (obj1->getLayer() < obj2->getLayer())				return true;
	else if (obj1->getLayer() > obj2->getLayer())			return false;

	else
	{
		if (obj1->getPosition().y < obj2->getPosition().y)	return true;
		else												return false;
	}
	//true일 경우 obj1과 obj2의 위치가 바뀐다.
}

void DRD2DEngine::ObjectRender()
{
	//모든 오브젝트 랜더
	const vector<Object*>& objs =
		gameEngine->getSceneManager()->getCurrnetScene()->getObjs();

// 	vector<Object*> objs = gameEngine->getSceneManager()->getCurrnetScene()->getObjs();
// 	std::sort(objs.begin(), objs.end(), sortLayer);

	for (size_t i = 0; i < objs.size(); i++)
	{
		objs[i]->render(renderTarget);
	}
}

void DRD2DEngine::ManagerRender()
{
	//디버깅용
	gameEngine->getCollisionManager()->render(renderTarget);
	gameEngine->getTimeManager()->render(renderTarget);
	//gameEngine->getMouseManager()->render(renderTarget);
}

void DRD2DEngine::Finalize()
{

}


ID2D1SolidColorBrush* DRD2DEngine::getBrush(COLOR _colorName)
{
	auto it = brushes.find(_colorName);
	if (it != brushes.end())
	{
		return it->second;
	}
	else
	{
		//저장된 색상 데이터를 찾지 못한 경우, 에러(마젠타) 브러쉬 반환
		return brushes[COLOR::MISSING];
	}
}


void DRD2DEngine::CreateBrushes()
{
	std::map<COLOR, int> colorTable = {
	{COLOR::AliceBlue, 0xF0F8FF},
	{COLOR::AntiqueWhite, 0xFAEBD7},
	{COLOR::Aqua, 0x00FFFF},
	{COLOR::Aquamarine, 0x7FFFD4},
	{COLOR::Azure, 0xF0FFFF},
	{COLOR::Beige, 0xF5F5DC},
	{COLOR::Bisque, 0xFFE4C4},
	{COLOR::Black, 0x000000},
	{COLOR::BlanchedAlmond, 0xFFEBCD},
	{COLOR::Blue, 0x0000FF},
	{COLOR::BlueViolet, 0x8A2BE2},
	{COLOR::Brown, 0xA52A2A},
	{COLOR::BurlyWood, 0xDEB887},
	{COLOR::CadetBlue, 0x5F9EA0},
	{COLOR::Chartreuse, 0x7FFF00},
	{COLOR::Chocolate, 0xD2691E},
	{COLOR::Coral, 0xFF7F50},
	{COLOR::CornflowerBlue, 0x6495ED},
	{COLOR::Cornsilk, 0xFFF8DC},
	{COLOR::Crimson, 0xDC143C},
	{COLOR::Cyan, 0x00FFFF},
	{COLOR::DarkBlue, 0x00008B},
	{COLOR::DarkCyan, 0x008B8B},
	{COLOR::DarkGoldenrod, 0xB8860B},
	{COLOR::DarkGray, 0xA9A9A9},
	{COLOR::DarkGreen, 0x006400},
	{COLOR::DarkKhaki, 0xBDB76B},
	{COLOR::DarkMagenta, 0x8B008B},
	{COLOR::DarkOliveGreen, 0x556B2F},
	{COLOR::DarkOrange, 0xFF8C00},
	{COLOR::DarkOrchid, 0x9932CC},
	{COLOR::DarkRed, 0x8B0000},
	{COLOR::DarkSalmon, 0xE9967A},
	{COLOR::DarkSeaGreen, 0x8FBC8F},
	{COLOR::DarkSlateBlue, 0x483D8B},
	{COLOR::DarkSlateGray, 0x2F4F4F},
	{COLOR::DarkTurquoise, 0x00CED1},
	{COLOR::DarkViolet, 0x9400D3},
	{COLOR::DeepPink, 0xFF1493},
	{COLOR::DeepSkyBlue, 0x00BFFF},
	{COLOR::DimGray, 0x696969},
	{COLOR::DodgerBlue, 0x1E90FF},
	{COLOR::Firebrick, 0xB22222},
	{COLOR::FloralWhite, 0xFFFAF0},
	{COLOR::ForestGreen, 0x228B22},
	{COLOR::Fuchsia, 0xFF00FF},
	{COLOR::Gainsboro, 0xDCDCDC},
	{COLOR::GhostWhite, 0xF8F8FF},
	{COLOR::Gold, 0xFFD700},
	{COLOR::Goldenrod, 0xDAA520},
	{COLOR::Gray, 0x808080},
	{COLOR::Green, 0x008000},
	{COLOR::GreenYellow, 0xADFF2F},
	{COLOR::Honeydew, 0xF0FFF0},
	{COLOR::HotPink, 0xFF69B4},
	{COLOR::IndianRed, 0xCD5C5C},
	{COLOR::Indigo, 0x4B0082},
	{COLOR::Ivory, 0xFFFFF0},
	{COLOR::Khaki, 0xF0E68C},
	{COLOR::Lavender, 0xE6E6FA},
	{COLOR::LavenderBlush, 0xFFF0F5},
	{COLOR::LawnGreen, 0x7CFC00},
	{COLOR::LemonChiffon, 0xFFFACD},
	{COLOR::LightBlue, 0xADD8E6},
	{COLOR::LightCoral, 0xF08080},
	{COLOR::LightCyan, 0xE0FFFF},
	{COLOR::LightGoldenrodYellow, 0xFAFAD2},
	{COLOR::LightGreen, 0x90EE90},
	{COLOR::LightGray, 0xD3D3D3},
	{COLOR::LightPink, 0xFFB6C1},
	{COLOR::LightSalmon, 0xFFA07A},
	{COLOR::LightSeaGreen, 0x20B2AA},
	{COLOR::LightSkyBlue, 0x87CEFA},
	{COLOR::LightSlateGray, 0x778899},
	{COLOR::LightSteelBlue, 0xB0C4DE},
	{COLOR::LightYellow, 0xFFFFE0},
	{COLOR::Lime, 0x00FF00},
	{COLOR::LimeGreen, 0x32CD32},
	{COLOR::Linen, 0xFAF0E6},
	{COLOR::Magenta, 0xFF00FF},
	{COLOR::Maroon, 0x800000},
	{COLOR::MediumAquamarine, 0x66CDAA},
	{COLOR::MediumBlue, 0x0000CD},
	{COLOR::MediumOrchid, 0xBA55D3},
	{COLOR::MediumPurple, 0x9370DB},
	{COLOR::MediumSeaGreen, 0x3CB371},
	{COLOR::MediumSlateBlue, 0x7B68EE},
	{COLOR::MediumSpringGreen, 0x00FA9A},
	{COLOR::MediumTurquoise, 0x48D1CC},
	{COLOR::MediumVioletRed, 0xC71585},
	{COLOR::MidnightBlue, 0x191970},
	{COLOR::MintCream, 0xF5FFFA},
	{COLOR::MistyRose, 0xFFE4E1},
	{COLOR::Moccasin, 0xFFE4B5},
	{COLOR::NavajoWhite, 0xFFDEAD},
	{COLOR::Navy, 0x000080},
	{COLOR::OldLace, 0xFDF5E6},
	{COLOR::Olive, 0x808000},
	{COLOR::OliveDrab, 0x6B8E23},
	{COLOR::Orange, 0xFFA500},
	{COLOR::OrangeRed, 0xFF4500},
	{COLOR::Orchid, 0xDA70D6},
	{COLOR::PaleGoldenrod, 0xEEE8AA},
	{COLOR::PaleGreen, 0x98FB98},
	{COLOR::PaleTurquoise, 0xAFEEEE},
	{COLOR::PaleVioletRed, 0xDB7093},
	{COLOR::PapayaWhip, 0xFFEFD5},
	{COLOR::PeachPuff, 0xFFDAB9},
	{COLOR::Peru, 0xCD853F},
	{COLOR::Pink, 0xFFC0CB},
	{COLOR::Plum, 0xDDA0DD},
	{COLOR::PowderBlue, 0xB0E0E6},
	{COLOR::Purple, 0x800080},
	{COLOR::Red, 0xFF0000},
	{COLOR::RosyBrown, 0xBC8F8F},
	{COLOR::RoyalBlue, 0x4169E1},
	{COLOR::SaddleBrown, 0x8B4513},
	{COLOR::Salmon, 0xFA8072},
	{COLOR::SandyBrown, 0xF4A460},
	{COLOR::SeaGreen, 0x2E8B57},
	{COLOR::SeaShell, 0xFFF5EE},
	{COLOR::Sienna, 0xA0522D},
	{COLOR::Silver, 0xC0C0C0},
	{COLOR::SkyBlue, 0x87CEEB},
	{COLOR::SlateBlue, 0x6A5ACD},
	{COLOR::SlateGray, 0x708090},
	{COLOR::Snow, 0xFFFAFA},
	{COLOR::SpringGreen, 0x00FF7F},
	{COLOR::SteelBlue, 0x4682B4},
	{COLOR::Tan, 0xD2B48C},
	{COLOR::Teal, 0x008080},
	{COLOR::Thistle, 0xD8BFD8},
	{COLOR::Tomato, 0xFF6347},
	{COLOR::Turquoise, 0x40E0D0},
	{COLOR::Violet, 0xEE82EE},
	{COLOR::Wheat, 0xF5DEB3},
	{COLOR::White, 0xFFFFFF},
	{COLOR::WhiteSmoke, 0xF5F5F5},
	{COLOR::Yellow, 0xFFFF00},
	{COLOR::YellowGreen, 0x9ACD32},
	{COLOR::MISSING, 0xFF00FF}
	};

	for (auto const& pair : colorTable)
	{
		//색상을 가져온다.
		D2D1_COLOR_F color;

		color.r = ((pair.second & 0xFF0000) >> 16) / 255.0f;
		color.g = ((pair.second & 0xFF00) >> 8) / 255.0f;
		color.b = ((pair.second & 0xFF)) / 255.0f;
		color.a = 1.0f;

		//브러쉬를 생성한다.
		ID2D1SolidColorBrush* brush;
		renderTarget->CreateSolidColorBrush(color, &brush);

		//map에 색상 이름과 브러쉬를 저장한다.
		brushes[pair.first] = brush;
		int a = 0;
	}
}




