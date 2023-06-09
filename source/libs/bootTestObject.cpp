#include "bootTestObject.h"

#include"scenemanager.h"

BootTestObject::BootTestObject(Scene* sc)
	:Object		(sc)
	, player	(Vec2{400,300})
	,radius		(50)
	,speed		(5)
	,freeStr	("")
{}
BootTestObject::~BootTestObject(){

}
void BootTestObject::Init(){

}
void BootTestObject::Update(){
	//Dash();
	//Move();
	
	SceneChangeKey();
}
void BootTestObject::Draw() {
	//プレイヤーの丸
	//DrawCircle(player.x, player.y, radius, 0xffffff, 20);


	//プレイヤーの　セリフ　位置
	int fontsize	= GetFontSize();
	int strsize		= freeStr.size() / 2;
	Vec2 strP		= player;
	strP.x -= fontsize * strsize;
	strP.y -= radius - 40;

	if (player.y < 300)
		strP.y = player.y + radius + 40;
	if (player.x < 400)
		strP.x = player.x - fontsize * strsize + 75 * 2;

	DrawFormatString(strP.x, strP.y, 0xffffff, freeStr.c_str());

	//上の説明
	std::string explanation = "";
	explanation += "仮のシーン　\n";
	explanation += "spaceKeyを押すとタイトルへ\n";
	explanation += "LshiftKeyを押すとゲームへ\n";
	DrawFormatString(100, 50, 0xff66ff,explanation.c_str());

	//編集用の主張
	int size = GetFontSize();
	std::string str = "仮";
	SetFontSize(96);
	
	DrawFormatString(400 - str.size() * 96 / 4, 600 - 128, 0xffffff, str.c_str());

	SetFontSize(size);
}

void BootTestObject::Move() {
	bool wKey	= CheckHitKey(KEY_INPUT_W);
	bool sKey	= CheckHitKey(KEY_INPUT_S);
	bool aKey	= CheckHitKey(KEY_INPUT_A);
	bool dKey	= CheckHitKey(KEY_INPUT_D);
	bool allKey = wKey || sKey || aKey || dKey;

	if (allKey) {
		freeStr = "自由だーーー！！";
	}
	else {
		freeStr = "";
	}

	if (wKey) {
		player.y = max(player.y-speed,0+radius);
		
		if (player.y < 1 + radius) {
			freeStr = "自由じゃない、？！";
		}
	}
	if (sKey) {
		player.y += speed;
		if (player.y > 600 - radius) {
			player.y = 600 - radius;
			freeStr = "自由じゃない、？！";
		}
	}

	if (aKey) {
		player.x -= speed;
		if (player.x < 0 + radius) {
			player.x = 0 + radius;
			freeStr = "自由じゃない、？！";
		}
	}
	if (dKey) {
		player.x += speed;
		if (player.x > 800 - radius) {
			player.x = 800 - radius;
			freeStr = "自由じゃない、？！";
		}
	}

	if (allKey && CheckHitKey(KEY_INPUT_T)) 
		freeStr = "絶対思考領域";
	
}
void BootTestObject::Dash(){
	bool lShift = CheckHitKey(KEY_INPUT_LSHIFT);
	
	lShift ? speed = 10 : speed = 5;
}

void BootTestObject::SceneChangeKey() {
	bool spaceKey	= CheckHitKey(KEY_INPUT_SPACE);
	bool lShiftKey	= CheckHitKey(KEY_INPUT_LSHIFT);
	
	if (spaceKey&& !lShiftKey) 
		SceneManager::SceneChange("Title");
	if (spaceKey&& lShiftKey) 
		SceneManager::SceneChange("Game");
}
