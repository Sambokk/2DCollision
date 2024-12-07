#include "pch.h"
#include "ResourceManager.h"

#include "GameEngine.h"
#include "DRD2DEngine.h"

ResourceManager::ResourceManager()
	:gameEngine(nullptr), wicFactory(nullptr), decoder(nullptr), frame(nullptr), converter(nullptr), renderTarget(nullptr)
	, imageUnfound(nullptr)
{
}

ResourceManager::~ResourceManager()
{
	wicFactory->Release();
	converter->Release();
	decoder->Release();
	frame->Release();
}

void ResourceManager::initialize(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
	renderTarget = gameEngine->getD2DEngine()->getRenderTarget();

	//wicFactory����
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));


	//�̹����� ã�� ������ �� ������ �̹��� �ε�
	loadImage(L"Unfound", L"..\\Resource\\unfound.png");
	imageUnfound = getImage(L"Unfound");
}




void ResourceManager::loadImage(const wstring& _name, const LPCWSTR& _path)
{
	HRESULT hr = S_OK;

	hr = wicFactory->CreateFormatConverter(&converter); //converter�� �Ź� ���� �ȸ���� �Ȱ��� �̹����� ���´�.......

	if (findImage(_name) == nullptr)
	{
		//�̹����� ���ڵ��ؼ� decoder�� ������ ��´�
		hr = wicFactory->CreateDecoderFromFilename(_path, nullptr, GENERIC_READ,
			WICDecodeMetadataCacheOnDemand, &decoder);


		//ù��° ������ ������ �����´�
		hr = decoder->GetFrame(0, &frame);


		//�̹����� direct2D ���� �������� ��ȯ
		converter->Initialize(frame,
			GUID_WICPixelFormat32bppPBGRA,  //dstFormat
			WICBitmapDitherTypeNone,		//dither
			nullptr,						//*pIPalette
			0.0f,							//alpha Threshold Percent
			WICBitmapPaletteTypeCustom		//paletteTranslate
		);

		//��Ʈ�� ����
		ID2D1Bitmap* bitmap;
		hr = renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &bitmap);


		//map�� ����
		images[_name] = bitmap;
	}
}

ID2D1Bitmap* ResourceManager::getImage(const wstring& _name)
{
	ID2D1Bitmap* img = findImage(_name);
	if (img == nullptr)
	{
		return imageUnfound;
	}

	return img;
}

ID2D1Bitmap* ResourceManager::findImage(const wstring& _name)
{
	map<wstring, ID2D1Bitmap*> ::iterator iter = images.find(_name);
	if (iter == images.end())
	{
		return nullptr;
	}

	return (ID2D1Bitmap*)iter->second;
}
