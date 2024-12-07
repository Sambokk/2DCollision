#pragma once

enum class KEY_STATE
{
	DOWN, //����X ����O
	HOLD, //����O ����O
	UP,   //����O ����X
	NONE  //����X ����X
};

enum class KEY
{
	LEFT, RIGHT, UP, DOWN,

	NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, NUM0,
	Q, W, E, R, T, Y, U, O,	P,
	A, S, D, F,	G, H, J, K, L,
	Z, X, C, V,	B, N, M,

	ALT, CTRL, LSHIFT,
	SPACE, ENTER, ESC, TAB,

	LMOUSE, RMOUSE,

	LAST, //enum�� ��
};

struct KeyInfo
{
	KEY_STATE state; // Ű�� ���°�
	bool      isPrevPush;  // ���� �����ӿ��� ���ȴ��� ����
};


class KeyManager
{

/// �����ڿ� �Ҹ���
	KeyManager();
	~KeyManager();

	friend class GameEngine;


/// �ɹ� ���� 
private:
	vector<KeyInfo> keyInfos;


/// �ɹ� �Լ�
public:
	void initialize();
	void update();

	KEY_STATE GetKeyState(KEY _key) { return keyInfos[(int)_key].state; }

};


