#pragma once
#include<DxLib.h>

class MouseState {
public:
	MouseState(int button);
	MouseState() { MouseState::MouseState(-1); }

	bool Down();//�������u��
	bool Up();//�������u��

	void Move(int* x,int* y);//�O�t���[������̈ړ���

	void Point(int* x,int* y);

	void Update();//�g��Update���̉��̕��ɒu���Ă�������
private:
	int myX, myY;

	int myButton;
	bool keystop;

};