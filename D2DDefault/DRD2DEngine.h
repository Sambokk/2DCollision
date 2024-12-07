#pragma once
#include "pch.h"
class GameEngine;

enum COLOR
{
	AliceBlue,
	AntiqueWhite,
	Aqua,
	Aquamarine,
	Azure,
	Beige,
	Bisque,
	Black,
	BlanchedAlmond,
	Blue,
	BlueViolet,
	Brown,
	BurlyWood,
	CadetBlue,
	Chartreuse,
	Chocolate,
	Coral,
	CornflowerBlue,
	Cornsilk,
	Crimson,
	Cyan,
	DarkBlue,
	DarkCyan,
	DarkGoldenrod,
	DarkGray,
	DarkGreen,
	DarkKhaki,
	DarkMagenta,
	DarkOliveGreen,
	DarkOrange,
	DarkOrchid,
	DarkRed,
	DarkSalmon,
	DarkSeaGreen,
	DarkSlateBlue,
	DarkSlateGray,
	DarkTurquoise,
	DarkViolet,
	DeepPink,
	DeepSkyBlue,
	DimGray,
	DodgerBlue,
	Firebrick,
	FloralWhite,
	ForestGreen,
	Fuchsia,
	Gainsboro,
	GhostWhite,
	Gold,
	Goldenrod,
	Gray,
	Green,
	GreenYellow,
	Honeydew,
	HotPink,
	IndianRed,
	Indigo,
	Ivory,
	Khaki,
	Lavender,
	LavenderBlush,
	LawnGreen,
	LemonChiffon,
	LightBlue,
	LightCoral,
	LightCyan,
	LightGoldenrodYellow,
	LightGreen,
	LightGray,
	LightPink,
	LightSalmon,
	LightSeaGreen,
	LightSkyBlue,
	LightSlateGray,
	LightSteelBlue,
	LightYellow,
	Lime,
	LimeGreen,
	Linen,
	Magenta,
	Maroon,
	MediumAquamarine,
	MediumBlue,
	MediumOrchid,
	MediumPurple,
	MediumSeaGreen,
	MediumSlateBlue,
	MediumSpringGreen,
	MediumTurquoise,
	MediumVioletRed,
	MidnightBlue,
	MintCream,
	MistyRose,
	Moccasin,
	NavajoWhite,
	Navy,
	OldLace,
	Olive,
	OliveDrab,
	Orange,
	OrangeRed,
	Orchid,
	PaleGoldenrod,
	PaleGreen,
	PaleTurquoise,
	PaleVioletRed,
	PapayaWhip,
	PeachPuff,
	Peru,
	Pink,
	Plum,
	PowderBlue,
	Purple,
	Red,
	RosyBrown,
	RoyalBlue,
	SaddleBrown,
	Salmon,
	SandyBrown,
	SeaGreen,
	SeaShell,
	Sienna,
	Silver,
	SkyBlue,
	SlateBlue,
	SlateGray,
	Snow,
	SpringGreen,
	SteelBlue,
	Tan,
	Teal,
	Thistle,
	Tomato,
	Turquoise,
	Violet,
	Wheat,
	White,
	WhiteSmoke,
	Yellow,
	YellowGreen,

	MISSING
};

class DRD2DEngine
{
///积己磊客 家戈磊
public:
	DRD2DEngine();
	~DRD2DEngine();


/// 干滚 窃荐
public:
	void Initialize(HWND hWnd, GameEngine* _gameEngine);

	void Loop();
	void Render();
	void Finalize();
	HRESULT CreateDeviceResources();
	ID2D1SolidColorBrush* getBrush(COLOR _colorName);
	IDWriteTextFormat* getDefaultTextFormat() { return defaultTextFormat; }
	ID2D1Factory* getFactory() { return direct2DFactory; }
	ID2D1HwndRenderTarget* getRenderTarget() { return renderTarget; }

private:
	void ObjectRender();
	void ManagerRender();
	void CreateBrushes();



///干滚 函荐
private:
	HWND hWnd;

	ID2D1Factory* direct2DFactory;
	IDWriteFactory* writeFactory;

	ID2D1HwndRenderTarget* renderTarget;
	GameEngine* gameEngine;

	map<COLOR, ID2D1SolidColorBrush*> brushes;
	IDWriteTextFormat* defaultTextFormat;


};


