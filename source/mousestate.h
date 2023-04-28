#pragma once
#include<DxLib.h>

class MouseState {
public:
	MouseState(int button);
	MouseState() { MouseState::MouseState(-1); }

	bool Down();//押した瞬間
	bool Up();//放した瞬間

	void Move(int* x,int* y);//前フレームからの移動量

	void Point(int* x,int* y);

	void Update();//使うUpdate内の下の方に置いてください
private:
	int myX, myY;

	int myButton;
	bool keystop;

};