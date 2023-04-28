#include "floor.h"

namespace {
	static const int GRAPHNUM = 2;
	std::string pass[GRAPHNUM] = { {"data/texture/wood-texture_00009.jpg"}
								 , {"data/texture/wood-texture_00010.jpg"}};
}

Floor::Floor(Scene* sc)
	:Object(sc)
	,hImage()
{}

Floor::~Floor(){
	for(int i=0;i<hImage.size();i++)
		if(hImage.at(i)>0)
			DeleteGraph(hImage.at(i));

}

void Floor::Init(){
	hImage.clear();

	hImage.resize(GRAPHNUM);
	for (int i = 0; i < hImage.size(); i++) {
		hImage.at(i) = LoadGraph(pass[i].c_str());
		assert(hImage.at(i) > 0);
	}

}

void Floor::Update(){

}

void Floor::Draw(){
	//for(int i=0;i<hImage.size();i++)
	//	DrawGraph(0,0+i*20,hImage.at(i),false);

	VERTEX3D vertex[6];
	for (int i = 0; i < 6; i++) {
		vertex[i].dif = GetColorU8(255, 255, 255, 255);
		vertex[i].spc = GetColorU8(0, 0, 0, 0);
		vertex[i].norm= VGet(0.0f, 0.0f, -1.0f);
		vertex[i].su  = 0.0f;
		vertex[i].sv  = 0.0f;

	}
	float size = 200;
	VECTOR pos=VGet(100,100,100);
	vertex[0].pos = pos;
	vertex[1].pos = pos+VGet(size,0,0);
	vertex[2].pos = pos+VGet(0, size,0);
	vertex[5].pos = pos+VGet(size, size,0);


	vertex[0].u = 0.0f;
	vertex[0].v = 0.0f;

	vertex[1].u = 1.0f;
	vertex[1].v = 0.0f;

	vertex[2].u = 0.0f;
	vertex[2].v = 1.0f;

	vertex[5].u = 1.0f;
	vertex[5].v = 1.0f;


	vertex[3]  = vertex[1];
	vertex[4]  = vertex[2];

	DrawPolygon3D(vertex,2,hImage.at(0),false);

}
