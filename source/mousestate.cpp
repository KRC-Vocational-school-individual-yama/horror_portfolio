#include "mousestate.h"

MouseState::MouseState(int button)
	:myButton(button)
	,keystop(false)
	,myX(0)
	,myY(0)
{
}

bool MouseState::Down(){
	return (GetMouseInput() & myButton)&&!keystop;
}

bool MouseState::Up(){
	return !(GetMouseInput() & myButton)&&keystop;
}

void MouseState::Move(int* x, int* y){
	int nowX=0, nowY=0;
	GetMousePoint(&nowX,&nowY);

	if (x != nullptr) {
		(*x) = nowX -myX;
	}
	if (y != nullptr) {
		(*y) = nowY -myY;
	}
}

void MouseState::Point(int* x, int* y){
	int nowX = 0, nowY = 0;
	GetMousePoint(&nowX, &nowY);

	if (x != nullptr) {
		(*x) = nowX ;
	}
	if (y != nullptr) {
		(*y) = nowY ;
	}
}

void MouseState::Update() {
	int x=0, y=0;
	GetMousePoint(&x,&y);

	myX		= x;
	myY		= y;
	keystop = (GetMouseInput()&myButton);
}