#include "graphDraw.h"
#include"keystate.h"
#include"libs/scene.h"
#include"skybox.h"

namespace {
	static const int divX = 0;
	static /*const*/ int divY = 0;
	KeyState* key;
}

GraphDraw::GraphDraw(Scene* sc)
	:Object(sc)
	,hImage(-1)
	,ver(nullptr)
{
	key = new KeyState(KEY_INPUT_P);

}

GraphDraw::~GraphDraw(){
	if (hImage > 0)
		DeleteGraph(hImage);
	if (ver != nullptr)
		delete[] ver;
	ver = nullptr;

}

void GraphDraw::Init(){
	if (ver != nullptr)
		delete[] ver;
	ver = nullptr;

	SkyBox* kp = GetScene()->Invoke<SkyBox>();


	hImage = LoadGraph("data/texture/sky_00009.jpg");
	assert(hImage > 0);

	Vec2 graphSize = {};
	GetGraphSize(hImage,&graphSize.x,&graphSize.y);
	size = VGet(graphSize.x,graphSize.y,0);

	dispPos = VGet(100,0,100);

	//divNum = {divX+1,divY+1};

	//int dNum= kp->GetDivNum();
	//divNum = {dNum,dNum};
	kp->GetDivNum(divNum.x,divNum.y);

	const int polygonNum = divNum.x * divNum.y;
	VERTEX3D* ver=new VERTEX3D[polygonNum*6];

	for (int i = 0; i < polygonNum; i++) {
		ver[i].dif = GetColorU8(255, 255, 255, 255);
		ver[i].spc = GetColorU8(0, 0, 0, 0);
		ver[i].norm = VGet(0.0f, 0.0f, -1.0f);
		ver[i].su = 0.0f;
		ver[i].sv = 0.0f;
	}

	VECTOR lenght = VGet(size.x/divNum.x,size.y/divNum.y,0);

	for (int j = 0; j < divNum.y; j++)
	for (int i = 0; i < divNum.x; i++) {
		int index = GetIndex(i,j);// i+j*divNum.x

		VECTOR pos = (dispPos +(VGet(i,j,0)*lenght)) /*+ VGet(0, size.y, 0)*/;
		ver[GetVertexIndex(0,index)].pos = pos;
		ver[GetVertexIndex(1,index)].pos = pos + VGet(lenght.x, 0, 0);
		ver[GetVertexIndex(2,index)].pos = pos + VGet(0, lenght.y, 0);//-
		ver[GetVertexIndex(3,index)].pos = ver[GetVertexIndex(1,index)].pos;
		ver[GetVertexIndex(4,index)].pos = ver[GetVertexIndex(2,index)].pos;
		ver[GetVertexIndex(5,index)].pos = pos + VGet(lenght.x, lenght.y, 0);//-

		//if ( 0+ (index+1) *6 > polygonNum )continue;

	}

	lenght = VGet(1.f / divNum.x, 1.f / divNum.y, 0);
	for (int j = 0; j < divNum.y; j++)
	for (int i = 0; i < divNum.x; i++) {
		int index = GetIndex(i, j);//i + j * divNum.x;

		VECTOR uv = VGet(i,j,0)*lenght;
		ver[GetVertexIndex(0,index)].u = uv.x;
		ver[GetVertexIndex(0,index)].v = uv.y;

		ver[GetVertexIndex(1,index)].u = uv.x +lenght.x;
		ver[GetVertexIndex(1,index)].v = uv.y;

		ver[GetVertexIndex(2,index)].u = uv.x;
		ver[GetVertexIndex(2,index)].v = uv.y+lenght.y;

		ver[GetVertexIndex(5,index)].u = uv.x+lenght.x;
		ver[GetVertexIndex(5,index)].v = uv.y+lenght.y;

		ver[GetVertexIndex(3,index)].u = ver[GetVertexIndex(1,index)].u;
		ver[GetVertexIndex(3,index)].v = ver[GetVertexIndex(1,index)].v;
								
		ver[GetVertexIndex(4,index)].u = ver[GetVertexIndex(2,index)].u;
		ver[GetVertexIndex(4,index)].v = ver[GetVertexIndex(2,index)].v;

	}

	for (int i = 0; i < polygonNum * 6; i++) {
		MATRIX rotZ = MGetRotZ(DX_PI);
		ver[i].pos= VTransform(ver[i].pos, rotZ);
	}


	/*VECTOR pos = dispPos+VGet(0,size.y,0);
	ver[0].pos = pos;
	ver[1].pos = pos + VGet(size.x, 0, 0);
	ver[2].pos = pos + VGet(0, -size.y, 0);
	ver[3].pos = ver[1].pos;
	ver[4].pos = ver[2].pos;
	ver[5].pos = pos + VGet(size.x, -size.y, 0);*/

	//int count = 0;
	//for (float i = 0; i < 1.0; i += (1/ divNum.x)) {
	//	ver[count].u = 0;		ver[1].u = i;
	//	ver[count*3+2].u = 0;		ver[5].u = i;
	//
	//	ver[3].u = ver[1].u;
	//	ver[4].u = ver[2].u;
	//
	//	ver[0].v = 0;
	//	ver[1].v = i;
	//	ver[2].v = 0;
	//	ver[5].v = i;
	//
	//	ver[3].v = ver[1].v;
	//	ver[4].v = ver[2].v;
	//	count++;
	//}

	//ver[0].u = 0.0f;
	//ver[0].v = 0.0f;
	//
	//ver[1].u = 1.0f;
	//ver[1].v = 0.0f;
	//
	//ver[2].u = 0.0f;
	//ver[2].v = 1.0f;
	//
	//ver[3].u = ver[1].u;
	//ver[3].v = ver[1].v;
	//
	//ver[4].u = ver[2].u;
	//ver[4].v = ver[2].v;
	//
	//ver[5].u = 1.0f;
	//ver[5].v = 1.0f;

	GraphDraw::ver = ver;

	//SkyBox* kp= GetScene()->Invoke<SkyBox>();
	//if (kp == nullptr)return;

	VertexIn(kp->GetSphereVertex());
}

void GraphDraw::Update(){
	if (key->Get()) {
		if (CheckHitKey(KEY_INPUT_LSHIFT)) {
			divY+= -2;
			if (divY < 0)divY = -1;
		}
		divY+= 1;

		Init();
	}

	//èdÇ¢
	//SkyBox* kp= GetScene()->Invoke<SkyBox>();
	//if(kp!=nullptr)
	//VertexIn(kp->GetSphereVertex());


	key->Update();
}

void GraphDraw::Draw(){
	//printfDx("Jkey ÇâüÇ∑Ç∆skyboxï\é¶êÿë÷\n");
	

	//MV1SetUseZBuffer();
	
	SetCameraNearFar(10.f, 100000.0f*2);//âìÇ≠Ç‹Ç≈é Ç∑

	const int polygonNum= divNum.x * divNum.y;
	DrawPolygon3D(ver, polygonNum * 2, hImage, true);

	SetDrawBlendMode(DX_BLENDMODE_ADD,255);

	DrawPolygon3D(ver, polygonNum*2,hImage,true);
	DrawPolygon3D(ver, polygonNum*2,hImage,true);
	DrawPolygon3D(ver, polygonNum*2,hImage,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	SetDrawScreen(DX_SCREEN_BACK);//ÉJÉÅÉâï`âÊãóó£ÇñﬂÇ∑
}

int GraphDraw::GetIndex(int _i, int _j){
	return _i + _j * divNum.x;
}

int GraphDraw::GetVertexIndex(int num, int index){
	int ans = num + index * 6;
	if (ans < 0)ans = 0;
	if (ans >= divNum.x * divNum.y * 6)ans = 0;
	return ans;

	//	Vec2 div = divNum;
	//	auto rambda = [index, div](int _num) {
	//		int ans = _num + index * 6;
	//		if (ans < 0)ans = 0;
	//		if (ans >= div.x * div.y * 6)ans = 0;
	//		return ans;
	//	};
}

void GraphDraw::VertexIn(std::vector<std::vector<VECTOR>>& vertexList) {

	for (int j = 0; j < divNum.y; j++)
	for (int i = 0; i < divNum.x; i++) {
		int index = GetIndex(i, j);// i+j*divNum.x

		int iIndex =  (i+1)%divNum.x;
		int jIndex =  j+1;
		//if (iIndex >= divNum.x)iIndex = divNum.x - 2;
		if (jIndex >= divNum.y)
			jIndex =j;

		ver[GetVertexIndex(0, index)].pos = vertexList.at(i)     .at(j);	 //lu
		ver[GetVertexIndex(2, index)].pos = vertexList.at(i)     .at(jIndex);//ld
		ver[GetVertexIndex(1, index)].pos = vertexList.at(iIndex).at(j);	 //ru
		ver[GetVertexIndex(5, index)].pos = vertexList.at(iIndex).at(jIndex);//rd
		
		ver[GetVertexIndex(3, index)].pos = ver[GetVertexIndex(1, index)].pos;
		ver[GetVertexIndex(4, index)].pos = ver[GetVertexIndex(2, index)].pos;
	}
}
