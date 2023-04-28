#include "gamescene.h"

#include<DxLib.h>
#include"libs/scenemanager.h"

#include"camera/camera.h"
#include"axis.h"
#include"item.h"
#include"floor.h"
#include"skybox.h"
#include"houseModel.h"
#include"debugString.h"
#include"frontString.h"
#include"flashLight.h"
#include"explanation.h"
#include"door.h"

GameScene::GameScene()
	:keystop{true}
{
	Create<Camera>();
	Create<Axis>();
	Create<Item>();
	Create<Floor>();
	Create<SkyBox>();
	//Create<GraphDraw>();
	Create<HouseModel>();
	Create<FrontString>();
	Create<Door>();

	ChangeDispRank(Invoke<FrontString>(), 100000);
	ChangeDispRank(Invoke<HouseModel>(), 50);

	Create<FlashLight>();

#ifdef _DEBUG
	Create<DebugString>();
	//dynamic_cast<DebugString*>(Create<DebugString>())->SetString("GameScene\nescape‚Å–ß‚é");
	Create<Explanation>();
#endif
}

GameScene::~GameScene(){
}

void GameScene::Update(){
	Scene::Update();

	bool backKey = CheckHitKey(KEY_INPUT_RETURN)
		||CheckHitKey(KEY_INPUT_ESCAPE);
	if (backKey && !keystop) {
		SceneManager::SceneChange("Title");
	}keystop = backKey;
}

void GameScene::Draw() {
	Scene::Draw();

	DrawCircle(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,5,0xffffff,false);
	DrawPixel(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,0xffffff);
	DrawPixel(SCREEN_WIDTH/2+1,SCREEN_HEIGHT/2,0xffffff);
	DrawPixel(SCREEN_WIDTH/2-1,SCREEN_HEIGHT/2,0xffffff);
	DrawPixel(SCREEN_WIDTH/2,SCREEN_HEIGHT/2+1,0xffffff);
	DrawPixel(SCREEN_WIDTH/2,SCREEN_HEIGHT/2-1,0xffffff);

	DrawFormatString(100,100,0xffffff,"GameScene\nescape‚Å–ß‚é");


#ifdef _DEBUG
	Invoke<DebugString>()->Draw();
	Invoke<Explanation>()->Draw();
#endif
}