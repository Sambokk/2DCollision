#pragma once

class GameEngine;
class DRD2DEngine;


/// <summary>
/// �̹����� �ҷ��� bitMap���� ��ȯ �� ���� & ����
/// </summary>
class ResourceManager
{
///�����ڿ� �Ҹ���
public:
	ResourceManager();
	~ResourceManager();
	void initialize(GameEngine* _gameEngine);
	

/// ��� ����
private:
	GameEngine* gameEngine;
	ID2D1HwndRenderTarget* renderTarget;

	IWICImagingFactory* wicFactory;
	IWICFormatConverter* converter;
	IWICBitmapDecoder* decoder;
	IWICBitmapFrameDecode* frame;

	map<wstring, ID2D1Bitmap*> images;
	ID2D1Bitmap* imageUnfound; //����Ÿ �̹���


///��� �Լ�
public:
	void loadImage(const wstring& _name, const LPCWSTR& _path); //�̹����� �о�ͼ� bitmap���� ����
	ID2D1Bitmap* getImage(const wstring& _name);


private:
	ID2D1Bitmap* findImage(const wstring& _name);
};


