#include "explanation.h"
#include"switchbutton.h"

namespace {
	SwitchButton* dispPkey=nullptr;
}

Explanation::Explanation(Scene* sc)
	:Object(sc)
	, str("")
	,hImage(-1)
	,fontHandle(-1)
	,backFontHandle(-1)
{
	dispPkey = new SwitchButton(KEY_INPUT_AT);
	dispPkey->On();
}

Explanation::~Explanation(){
	if (dispPkey != nullptr)
		delete dispPkey;
	if (hImage > 0)
		DeleteGraph(hImage);
	if (fontHandle > 0)
		DeleteFontToHandle(fontHandle);
	if (backFontHandle > 0)
		DeleteFontToHandle(backFontHandle);
}

void Explanation::Init(){
	hImage = LoadGraph("data/texture/paper_00112.jpg");
	assert(hImage > 0);
	fontHandle = CreateFontToHandle(NULL,64,-1,DX_FONTTYPE_ANTIALIASING_EDGE,-1,8);
	assert(fontHandle > 0);
	backFontHandle = CreateFontToHandle(NULL,GetFontSize()+8, -1, DX_FONTTYPE_ANTIALIASING_EDGE, -1);
	assert(backFontHandle > 0);

	str = "";

	str += "Escape , Enter �L�[�������ƃ^�C�g���֖߂�@�@@�L�[�ł��̉�ʂ����\n";
	str += "\n";
	str += "�J��������@\n";
	str += "�@�E�N���b�N�� �@���_����\n";
	str += "�@wasd�L�[�� �@�@�J�����ړ�\n";
	str += "�@Lcontrol�L�[�� �J���������ʒu\n";
	str += "\n";
	str += "���C�g�ؑ�\n";
	str += "�@L�L�[�� ���C�g�ؑ�\n";
	str += "\n";
	str += "axis�̕\��\n";
	str += "�@O�L�[�� �ؑ�\n";
	str += "\n";
	str += "skybox�̉摜�ɂ���\n";
	str += "�@P�L�[�� �@�@�@�@�@�������𑝂₷ �@+ Init��ǂݒ���\n";
	str += "�@P + Lshift �L�[�� �����������炷 �@+ Init��ǂݒ���\n";
	str += "skybox��vertex�ɂ���\n";
	str += "�@K�L�[�� �@�@�@�@�@�J�����ʒu�Ɉړ� + Init��ǂݒ���\n";
	str += "�@H + Lshift �L�[�� �������𑝂₷ �@+ Init��ǂݒ���\n";
	str += "�@H�L�[�� �@�@�@�@�@�����������炷 �@+ Init��ǂݒ���\n";
	str += "�@O + Rshift �L�[�� skybox�̃K�C�h���\���ؑ�\n";
	str += "�@J�L�[�� �@�@�@�@�@�O���t�\���ؑ�\n";
	str += "�@M�L�[�� �@�@�@�@�@�O���t��]�@�i�d���j�i������K�L�[�œǂݍ��݁j\n";
	str += "\n";

}

void Explanation::Update(){

	dispPkey->Update();
}

void Explanation::Draw(){
	if (dispPkey->Get()) {
		DrawStringToHandle(0, SCREEN_HEIGHT - (GetFontSize()+8), "@�L�[�Ő������", 0xffffff, backFontHandle, 0x0);
		return;
	}

	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0xffffff,true);
	DrawExtendGraph(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,hImage,false);


	SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	DrawStringToHandle(200,50,"��������i���j",0x0,fontHandle,0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawString(100,150,str.c_str(),0x0);


	DrawString(0,SCREEN_HEIGHT-GetFontSize(),"@�L�[�ŉ�ʂ����",0x0);
}
