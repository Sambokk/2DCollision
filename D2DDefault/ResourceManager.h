#pragma once

class GameEngine;
class DRD2DEngine;


/// <summary>
/// 이미지를 불러와 bitMap으로 변환 후 저장 & 관리
/// </summary>
class ResourceManager
{
///생성자와 소멸자
public:
	ResourceManager();
	~ResourceManager();
	void initialize(GameEngine* _gameEngine);
	

/// 멤버 변수
private:
	GameEngine* gameEngine;
	ID2D1HwndRenderTarget* renderTarget;

	IWICImagingFactory* wicFactory;
	IWICFormatConverter* converter;
	IWICBitmapDecoder* decoder;
	IWICBitmapFrameDecode* frame;

	map<wstring, ID2D1Bitmap*> images;
	ID2D1Bitmap* imageUnfound; //마젠타 이미지


///멤버 함수
public:
	void loadImage(const wstring& _name, const LPCWSTR& _path); //이미지를 읽어와서 bitmap으로 저장
	ID2D1Bitmap* getImage(const wstring& _name);


private:
	ID2D1Bitmap* findImage(const wstring& _name);
};


