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

	// ���ʂ��킩��Ղ��悤�ɕW�����C�g�𖳌���
	//SetLightEnable(FALSE);

	VECTOR fastPos=VGet(0,0,0);
	if (CheckClass<Camera>()) 
	fastPos = GetScene()->Invoke<Camera>()->GetPos();
	
	//�X�|�b�g���C�g 
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

	//�|�C���g���C�g
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

	//VECTOR Position �F ���C�g�̈ʒu
		//VECTOR Direction �F ���C�g�̌���
		//float OutAngle �F �X�|�b�g���C�g�R�[���̊O���̊p�x( �P�ʁF���W�A�� )
		//float InAngle �F �X�|�b�g���C�g�R�[���̓����̊p�x( �P�ʁF���W�A�� )
		//float Range �F ���C�g�̗L������
		//float Atten0 �F ���������p�����[�^�O
		//float Atten1 �F ���������p�����[�^�P
		//float Atten2 �F ���������p�����[�^�Q
}

void FlashLight::Update(){
	if (onkey->Get()) {
		if (!on) {
			 on = true;

			Init();
			// ���ʂ��킩��Ղ��悤�ɕW�����C�g�𖳌���
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

			// �W�����C�g��L����
			SetLightEnable(TRUE);
		}
	}

	onkey->Update();

	if ( !on)return;

	if ( !CheckClass<Camera>()) return;
	Camera* cp = GetScene()->Invoke<Camera>();
	VECTOR pos = cp->GetPos();
	VECTOR dir = cp->GetDir();// *VGet(0.1f, 0.1f, 0.1f);


	//�X�|�b�g���C�g
	if(lightHandle>0)
	{
		dir = cp->GetDir();// *VGet(0.1f, 0.1f, 0.1f);
		SetLightDirectionHandle(lightHandle, dir);
		SetLightPositionHandle(lightHandle, cp->GetPos());


		//���@������
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

	//�|�C���g���C�g
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
