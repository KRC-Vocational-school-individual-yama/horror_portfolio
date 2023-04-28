#include "flashLight.h"
#include"libs/scene.h"
#include"camera/camera.h"
//#include"keystate.h"
#include"switchbutton.h"

namespace {
	SwitchButton* onkey = nullptr;
//	KeyState* onkey=nullptr;
}
#define SPOT_LIGHT
//#define POINT_LIGHT

FlashLight::FlashLight(Scene* sc)
	:Object(sc)
	,lightHandle{-1}
	,lightHandle2{-1}
	,on{false}
{
	onkey = new SwitchButton(KEY_INPUT_L);

}

FlashLight::~FlashLight()
{
	if(lightHandle>0)
		DeleteLightHandle(lightHandle);

	if(lightHandle2>0)
		DeleteLightHandle(lightHandle2);

	if(onkey!=nullptr)
		delete onkey;
}

void FlashLight::Init()
{
	if ( !on)return;

	// 効果がわかり易いように標準ライトを無効化
	//SetLightEnable(FALSE);

	VECTOR fastPos=VGet(0,0,0);
	if (CheckClass<Camera>()) 
	fastPos = GetScene()->Invoke<Camera>()->GetPos();
	
	//スポットライト 
#ifdef SPOT_LIGHT
	{
		lightHandle = CreateSpotLightHandle(
			fastPos, VGet(0.0f,0.0f,1.0f),
			DX_PI_F/180.f*90.f,//		DX_PI_F / 2.0f,
			DX_PI_F/180.f*45.f,//		DX_PI_F / 4.0f,
			5000.0f,
			0.0f,
			0.0002f,
			0.0000005f
		);
	assert(lightHandle > 0);
	}
#endif

	//ポイントライト
#ifdef POINT_LIGHT
	{

		lightHandle2 = CreatePointLightHandle(
			fastPos,
			8000.0f,
			0.3f,
			0.0006f,
			0.0000040f
		);
	}
	assert(lightHandle2 > 0);
#endif

	//VECTOR Position ： ライトの位置
		//VECTOR Direction ： ライトの向き
		//float OutAngle ： スポットライトコーンの外側の角度( 単位：ラジアン )
		//float InAngle ： スポットライトコーンの内側の角度( 単位：ラジアン )
		//float Range ： ライトの有効距離
		//float Atten0 ： 距離減衰パラメータ０
		//float Atten1 ： 距離減衰パラメータ１
		//float Atten2 ： 距離減衰パラメータ２
}

void FlashLight::Update(){
	if (onkey->Get()) {
		if (!on) {
			 on = true;

			Init();
			// 効果がわかり易いように標準ライトを無効化
			SetLightEnable(FALSE);
		}

	}
	else {
		if (on) {
			on = false;

			if (lightHandle > 0)
				DeleteLightHandle(lightHandle);
			if (lightHandle2 > 0)
				DeleteLightHandle(lightHandle2);

			// 標準ライトを有効化
			SetLightEnable(TRUE);
		}
	}

	onkey->Update();

	if ( !on)return;

	if ( !CheckClass<Camera>()) return;
	Camera* cp = GetScene()->Invoke<Camera>();
	VECTOR pos = cp->GetPos();
	VECTOR dir = cp->GetDir();// *VGet(0.1f, 0.1f, 0.1f);


	//スポットライト
	if(lightHandle>0)
	{
		dir = cp->GetDir();// *VGet(0.1f, 0.1f, 0.1f);
		SetLightDirectionHandle(lightHandle, dir);
		SetLightPositionHandle(lightHandle, cp->GetPos());


		//仮　お試し
		//float num = (count % 360);
		//if (CheckHitKey(KEY_INPUT_F))
		//	dir= VTransform(dir, MGetRotY(DX_PI_F/180*num));
		//
		//if (CheckHitKey(KEY_INPUT_H))
		//	dir= VTransform(dir, MGetRotY(DX_PI_F/180*-num));
		//
		//
		//SetLightDirectionHandle(lightHandle, dir);
	}

	//ポイントライト
	if(lightHandle2>0)
	{

		dir = VScale(VNorm(dir), 600.f);

		VECTOR ans = VTransform(pos, MGetTranslate(dir));

		
		SetLightPositionHandle(lightHandle2, ans);
	}

}

void FlashLight::Draw(){
	VECTOR disp;
#ifdef SPOT_LIGHT
	//printfDx("\n");
	//
	//disp= GetLightPositionHandle(lightHandle);
	//printfDx("flash Spot Light Pos : x_ %.1f ,y_ %.1f, z_ %.1f \n",disp.x,disp.y,disp.z);
	//disp = GetLightDirectionHandle(lightHandle);
	//printfDx("flash Spot Light Dir : x_ %.1f ,y_ %.1f, z_ %.1f \n",disp.x,disp.y,disp.z);
#endif

#ifdef POINT_LIGHT
	//printfDx("\n");
	//
	//disp= GetLightPositionHandle(lightHandle2);
	//printfDx("flash Point Light Pos : x_ %.1f ,y_ %.1f, z_ %.1f \n",disp.x,disp.y,disp.z);
	//disp = GetLightDirectionHandle(lightHandle2);
	//printfDx("flash Point Light Dir : x_ %.1f ,y_ %.1f, z_ %.1f \n",disp.x,disp.y,disp.z);
#endif
}
