#include "houseModel.h"
#include"debugString.h"
#include"libs/scene.h"

HouseModel::HouseModel(Scene* sc)
	:Object(sc)
	,hModel(-1)
{
}

HouseModel::~HouseModel()
{
	if(hModel>0)
		MV1DeleteModel(hModel);
}

void HouseModel::Init()
{
	hModel = MV1LoadModel("data/model/room/174_room.mv1");
	assert(hModel>0);
	
	//if(CheckClass<DebugString>())
	//	GetScene()->Invoke<DebugString>()->SetString("houseModel");	


	MV1SetScale(hModel,MV1GetScale(hModel)*VGet(10,10,10));
}

void HouseModel::Update()
{
}

void HouseModel::Draw()
{
	MV1DrawModel(hModel);
	
	//è∞

	VERTEX3D poly[6];
	for (int i = 0; i < 6; i++) {
		poly[i].norm= VGet(0,0,-1);
		poly[i].dif = GetColorU8(255, 255, 255,255);
		poly[i].spc = GetColorU8(0,0,0,0);
		poly[i].su  = 0;
		poly[i].sv  = 0;
	}
	float size = 20000;
	VECTOR pos = VGet(size/-2,0,size/-2);
	poly[0].pos = pos+VGet(0,0,0);
	poly[1].pos = pos+VGet(size,0,0);
	poly[2].pos = pos+VGet(0,0, size);
	poly[3].pos = poly[1].pos;
	poly[4].pos = poly[2].pos;
	poly[5].pos = pos+VGet(size,0, size);
	
	/*ToDo:âº å„ïœçX*/DrawPolygon3D(poly, 2, DX_NONE_GRAPH, false);
}
