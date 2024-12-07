#define _USE_MATH_DEFINES
#include "pch.h"
#include "Convex.h"

#include "GameEngine.h"
#include "DRD2DEngine.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Vector2.h"
#include "function.h"
#include "Rigidbody.h"

Convex::Convex(GameEngine* _gameEngine)
{
	gameEngine = _gameEngine;
}

Convex::Convex(GameEngine* _gameEngine, vector<Vector2> _vertex)
{
	gameEngine = _gameEngine;
	vertexs = _vertex;

	//회전을 위한 중심좌표를 구한다.
	for (size_t i = 0; i < _vertex.size(); i++)
	{
		position = position + _vertex[i];
	}
	position = position / (float)_vertex.size();

	//중심좌표로 부터 상대좌표를 구한다.
	for (size_t i = 0; i < _vertex.size(); i++)
	{
		relativeVertexs.push_back(_vertex[i] - position);
	}

	collider = new Collider(this, vertexs, 0);

	createRigidbody(10.f, 1.f);
	rigidbody->setType(Rigidbody::TYPE::STATIC);
}

Convex::~Convex()
{
}

void Convex::update()
{
	vertexs.clear();
	vector<Vector2> tempRV;

	//회전변환, 위치변환
	float radian = rotation * (float)M_PI / 180.f;

	for (size_t i = 0; i < relativeVertexs.size(); i++)
	{
		tempRV.push_back(RotateVertex(relativeVertexs[i], radian)); //회전
		vertexs.push_back(tempRV[i] + position); //위치
	}
}

void Convex::render(ID2D1HwndRenderTarget* _renderTarget)
{
	//화면 출력을 위한 좌표로 변환
	int m_size = vertexs.size();
	D2D1_POINT_2F* pointArr = new  D2D1_POINT_2F[m_size];

	for (int i = 0; i < m_size - 1; i++)
	{
		pointArr[i] = D2D1::Point2F(vertexs[i].x, vertexs[i].y);
	}


	//선분 조각들로 구성된 기하 경로를 생성
	ID2D1PathGeometry* geo = nullptr;
	gameEngine->getD2DEngine()->getFactory()->CreatePathGeometry(&geo);

	//경로 기하에 조각들을 기록하기 위해 기하 싱크를 얻음
	ID2D1GeometrySink* sink = nullptr;
	geo->Open(&sink);

	//피규어의 시작(피규어의 시작점, 채우기 or 비우기)
	sink->BeginFigure(D2D1::Point2F(vertexs[m_size - 1].x, vertexs[m_size - 1].y), D2D1_FIGURE_BEGIN_FILLED);

	//조각 추가
	sink->AddLines(pointArr, m_size - 1);

	//피규어의 끝
	sink->EndFigure(D2D1_FIGURE_END_CLOSED);
	sink->Close();


	//화면에 기하경로 그리기
	_renderTarget->DrawGeometry(
		geo,
		gameEngine->getD2DEngine()->getBrush(COLOR::Wheat),
		2.f,
		0);

	_renderTarget->FillGeometry(
		geo, gameEngine->getD2DEngine()->getBrush(COLOR::Wheat));


	//delete geo;
	//delete sink;
	delete[] pointArr;
}

void Convex::OnCollisionEnter(Object* _other, Vector2 _depth)
{

}

void Convex::OnCollision(Object* _other, Vector2 _depth)
{
	if (_other->getName() != L"move" && _other->getName() != L"obs")
	{
		Vector2 pos = _other->getPosition();
		pos += _depth;
		_other->setPosition(pos);
	}

	if (_other->getName() == L"obs")
	{
		position -= _depth;
	}
}
