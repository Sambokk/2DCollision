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

	//wicFactory생성
	HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr,
		CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));


	//이미지를 찾지 못했을 때 보여줄 이미지 로드
	loadImage(L"Unfound", L"..\\Resource\\unfound.png");
	imageUnfound = getImage(L"Unfound");
}




void ResourceManager::loadImage(const wstring& _name, const LPCWSTR& _path)
{
	HRESULT hr = S_OK;

	hr = wicFactory->CreateFormatConverter(&converter); //converter를 매번 새로 안만들면 똑같은 이미지만 나온다.......

	if (findImage(_name) == nullptr)
	{
		//이미지를 디코딩해서 decoder에 정보를 담는다
		hr = wicFactory->CreateDecoderFromFilename(_path, nullptr, GENERIC_READ,
			WICDecodeMetadataCacheOnDemand, &decoder);


		//첫번째 프레임 정보를 가져온다
		hr = decoder->GetFrame(0, &frame);


		//이미지를 direct2D 전용 포멧으로 변환
		converter->Initialize(frame,
			GUID_WICPixelFormat32bppPBGRA,  //dstFormat
			WICBitmapDitherTypeNone,		//dither
			nullptr,						//*pIPalette
			0.0f,							//alpha Threshold Percent
			WICBitmapPaletteTypeCustom		//paletteTranslate
		);

		//비트맵 생성
		ID2D1Bitmap* bitmap;
		hr = renderTarget->CreateBitmapFromWicBitmap(converter, nullptr, &bitmap);


		//map에 저장
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
