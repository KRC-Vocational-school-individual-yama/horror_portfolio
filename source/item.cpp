#include "item.h"
#include"switchbutton.h"
#include"keystate.h"
#include"camera/camera.h"
#include"libs/scene.h"
#include"frontString.h"
#include"door.h"

namespace {
	SwitchButton* button;
	KeyState* openKey = nullptr;
	std::string  itemStr= "Eキーでドアを開ける";
}

Item::Item(Scene* sc)
	:Object(sc)
	, transform()
{}

Item::~Item() {
	if (button != nullptr)
		delete button;
	if (openKey != nullptr)
		delete openKey;
}

void Item::Init() {
	transform.position = VGet(50, 200*6, 50);
	button = new SwitchButton(-1);
	openKey = new KeyState(KEY_INPUT_E);
}

void Item::Update() {
	//mouse
	int x, y;
	GetMousePoint(&x, &y);

	x = SCREEN_WIDTH / 2;
	y = SCREEN_HEIGHT / 2;

	VECTOR col = ConvScreenPosToWorldPos(VGet(x, y, 0));
	VECTOR col2 = ConvScreenPosToWorldPos(VGet(x, y, 1));

	float length = Segment_Point_MinLength(col, col2, transform.position);

	if (length < 50.f) {
		button->On();
		/*ToDo:一行下後で消す*/
		//if( !CheckCameraViewClip(transform.position)); //貫通意味ない
		if (!ons) {
			if (CheckClass<FrontString>()) {
				FrontString* fp = GetScene()->Invoke<FrontString>();
				fp->DrawCreateFont(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 2, itemStr.c_str(), 0xffffff, NULL, 32, -1, DX_FONTTYPE_EDGE);
			}
			ons = true;
		}

	}
	else {
		button->Off();
		if (ons) {
			if (CheckClass<FrontString>()) {
				GetScene()->Invoke<FrontString>()->DeleteFont(itemStr);
			}

			ons = false;
		}
	}



	if (button->Get()) {
		bool open = openKey->Down()
			||(GetMouseInput() & MOUSE_INPUT_LEFT)
			;
		if (open) {
			if (CheckClass<Door>()) {
				GetScene()->Invoke<Door>()->Open();
			}
		}
	}



	button->Update();
	openKey->Update();
}

void Item::Draw(){
	//printfDx();

	transform.MakeMatrix();

	DrawSphere3D(transform.position,50,13,0xffffff,0xffffff,button->Get());

}
