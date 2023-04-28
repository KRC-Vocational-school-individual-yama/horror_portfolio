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

	str += "Escape , Enter キーを押すとタイトルへ戻る　　@キーでこの画面を閉じる\n";
	str += "\n";
	str += "カメラ操作　\n";
	str += "　右クリックで 　視点方向\n";
	str += "　wasdキーで 　　カメラ移動\n";
	str += "　Lcontrolキーで カメラ初期位置\n";
	str += "\n";
	str += "ライト切替\n";
	str += "　Lキーで ライト切替\n";
	str += "\n";
	str += "axisの表示\n";
	str += "　Oキーで 切替\n";
	str += "\n";
	str += "skyboxの画像について\n";
	str += "　Pキーで 　　　　　分割数を増やす 　+ Initを読み直し\n";
	str += "　P + Lshift キーで 分割数を減らす 　+ Initを読み直し\n";
	str += "skyboxのvertexについて\n";
	str += "　Kキーで 　　　　　カメラ位置に移動 + Initを読み直し\n";
	str += "　H + Lshift キーで 分割数を増やす 　+ Initを読み直し\n";
	str += "　Hキーで 　　　　　分割数を減らす 　+ Initを読み直し\n";
	str += "　O + Rshift キーで skyboxのガイド線表示切替\n";
	str += "　Jキーで 　　　　　グラフ表示切替\n";
	str += "　Mキーで 　　　　　グラフ回転　（重い）（同時にKキーで読み込み）\n";
	str += "\n";

}

void Explanation::Update(){

	dispPkey->Update();
}

void Explanation::Draw(){
	if (dispPkey->Get()) {
		DrawStringToHandle(0, SCREEN_HEIGHT - (GetFontSize()+8), "@キーで説明画面", 0xffffff, backFontHandle, 0x0);
		return;
	}

	DrawBox(0,0,SCREEN_WIDTH,SCREEN_HEIGHT,0xffffff,true);
	DrawExtendGraph(0,0,SCREEN_WIDTH, SCREEN_HEIGHT,hImage,false);


	SetDrawBlendMode(DX_BLENDMODE_SUB, 255);
	DrawStringToHandle(200,50,"操作説明（仮）",0x0,fontHandle,0xffffff);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawString(100,150,str.c_str(),0x0);


	DrawString(0,SCREEN_HEIGHT-GetFontSize(),"@キーで画面を閉じる",0x0);
}
