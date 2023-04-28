#include "axis.h"
#include"switchbutton.h"

namespace {
	SwitchButton* button;
}

Axis::Axis(Scene* sc)
	:Object(sc)
{
	button = new SwitchButton(KEY_INPUT_O);
}

Axis::~Axis()
{
	delete button;
}

void Axis::Init()
{
	button->On();
}

void Axis::Update()
{
	button->Update();
}

void Axis::Draw()
{
	if ( !button->Get())return;
	float lenght = 10000;
	DrawLine3D(VGet(0,0,0),VGet(lenght,0,0),0xff5555);
	DrawLine3D(VGet(0,0,0),VGet(0, lenght,0),0x55ff55);
	DrawLine3D(VGet(0,0,0),VGet(0,0, lenght),0x5555ff);

	lenght = 15;
	VECTOR disp= ConvScreenPosToWorldPos(VGet(100, SCREEN_HEIGHT - 100, 0.5f));
	DrawLine3D(disp, VAdd(disp, VGet(lenght,0,0)),0xff5555);
	DrawLine3D(disp, VAdd(disp, VGet(0, lenght,0)),0x55ff55);
	DrawLine3D(disp, VAdd(disp, VGet(0,0, lenght)),0x5555ff);

}
