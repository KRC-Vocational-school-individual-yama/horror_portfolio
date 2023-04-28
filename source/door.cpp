#include "door.h"
#include"save.h"
#include"switchbutton.h"
#include"keystate.h"

namespace {
	SwitchButton* saveButton;
	KeyState* animReset = nullptr;
	SwitchButton* animFlag = nullptr;
	SwitchButton* animChange = nullptr;

	static const int MAX_H_TEXTURE=2;
	int modelTexture[MAX_H_TEXTURE];
	char passTexture[MAX_H_TEXTURE][256] = {
		"data/model/door/Door_C.jpg"//"data/texture/sky_00009.jpg"
	   ,"data/model/door/Reflexion.jpg"
	};


}

Door::Door(Scene* sc)
	:Object(sc)
	,hModel{-1}
	,transform()
	,animCount{0}
	,hAnimNumber{-1}
{
}

Door::~Door()
{
	if (hModel > 0)
		MV1DeleteModel(hModel);
	if(saveButton!=nullptr)
		delete saveButton;
	if (animReset != nullptr)
		delete animReset;
	if (animFlag != nullptr)
		delete animFlag;
	if (animChange != nullptr)
		delete animChange;

	for(int i = 0; i < MAX_H_TEXTURE; i++) {
		if (modelTexture[i] > 0)
			DeleteGraph(modelTexture[i]);
	}

}

void Door::Init()
{
	hModel = MV1LoadModel("data/model/door/Door_Component_BI3.mv1");
	assert(hModel > 0);

	saveButton = new SwitchButton(KEY_INPUT_NUMPAD3);
	saveButton->Off();
	animReset = new KeyState(KEY_INPUT_NUMPAD1);
	animFlag = new SwitchButton(KEY_INPUT_NUMPAD5);
	animChange = new SwitchButton(KEY_INPUT_NUMPAD0);

	for (int i = 0; i < MAX_H_TEXTURE; i++) {
		modelTexture[i] = LoadGraph(passTexture[i]);
		assert(modelTexture[i] > 0);
	}




	transform.position = VGet(1836, 100, 1500);
	transform.scale = VScale(VGet(1, 1, 1), 9);
	transform.rotation = VGet(0, DX_PI_F / 2, 0);

	transform.MakeMatrix();
	MV1SetMatrix(hModel, transform.matrix);


	//for (int i = 0; i < MAX_H_TEXTURE; i++) {
	//	MV1SetTextureGraphHandle(hModel, i, modelTexture[i], false);
	//}


	hAnimNumber=MV1AttachAnim(hModel, 0);//アニメーションモデルの番号を指定
	int hNum=MV1AttachAnim(hModel, 8);

	animMaxCount = MV1GetAnimTotalTime(hModel, hAnimNumber);

}

	//MV1SetLoadCalcPhysicsWorldGravity();
void Door::Update()
{
	if (animReset->Get()) {
		animCount = 0;
	}

	
	if (animFlag->Get()) {
		if (animMaxCount/2 >= animCount)
			animCount++;
	}
	else {
		animCount = max(animCount-1,0);
	}
	if (animChange->Get())
		hAnimNumber=1;
	else
		hAnimNumber=0;


#ifdef _DEBUG
	Move();
	TextOutput();

	saveButton->Update();
#endif

	animReset->Update();
	animFlag->Update();
	animChange->Update();

}

void Door::Draw()
{
	transform.MakeMatrix();
	MV1SetMatrix(hModel, transform.matrix);


	MV1SetAttachAnimTime(hModel, hAnimNumber, animCount);

#if false//def _DEBUG
	MV1DrawModelDebug(hModel,0xdddddd,0,1,1,0);
#else
	MV1DrawModel(hModel);
#endif
	printfDx("door animmasion count = %.0f\n", MV1GetAttachAnimTime(hModel, hAnimNumber));
	printfDx("animNumber = %d\n", hAnimNumber);
}

void Door::Open(){
	animFlag->On();
}

std::string Door::InValueToString(VECTOR v){
	std::string str = "";
	str +=std::to_string( v.x);
	str += " ";
	str +=std::to_string( v.y);
	str += " ";
	str +=std::to_string( v.z);

	return str;
}

void Door::TextOutput(){

	if (saveButton->Get()) {
		std::vector<std::string> out;
		out.emplace_back("position"+ InValueToString(transform.position));
		

		CsvSave::Save("txt/doorMarix.txt",out,out.size());
		saveButton->Off();
	}
}

void Door::Move(){
bool up		= CheckHitKey(KEY_INPUT_NUMPAD9);
	bool down	= CheckHitKey(KEY_INPUT_NUMPAD7);

	bool flont	= CheckHitKey(KEY_INPUT_NUMPAD8);
	bool back	= CheckHitKey(KEY_INPUT_NUMPAD2);

	bool left	= CheckHitKey(KEY_INPUT_NUMPAD4);
	bool right	= CheckHitKey(KEY_INPUT_NUMPAD6);


	if (up) {
		transform.position.y++;
	}
	else if (down) {
		transform.position.y--;
	}

	if (flont) {
		transform.position.z++;

	}
	else if (back) {
		transform.position.z--;

	}

	if (right) {
		transform.position.x++;

	}
	else if (left) {
		transform.position.x--;

	}

}
