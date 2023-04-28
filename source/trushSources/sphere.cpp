#include "sphere.h"

namespace {
	static const int Division_number =360;
}

Sphere::Sphere(Scene* sc)
	:Object(sc)
	,transform()
	,vertex()
{
	vertex.clear();
}

Sphere::~Sphere(){

}

void Sphere::Init(){
	vertex.reserve(Division_number);

	transform.position = VGet(500,300,500);

	float radius = 100;
	MATRIX move = MGetTranslate(VGet(0,0,radius));
	
	for (int i = 0; i < Division_number; i++) {
		float rad = DX_PI_F / 180 * i;

		MATRIX rotY = MGetRotY(rad);

		VECTOR pos = VTransform(VGet(0,0,1), move * rotY);
		vertex.emplace_back(pos);
	}
	vertex.shrink_to_fit();

	for (int i = 0; i < vertex.size(); i++) {
		float rad = DX_PI_F / 180 * 90;
		MATRIX rotX = MGetRotX(rad);
		VECTOR temp= vertex.at(i);

		vertex.at(i) = temp*rotX;

	}
	for (int j = 0; j < Division_number; j++) {
		std::vector<VECTOR> ans;
		for (int i = 0; i < vertex.size(); i++) {
	
			float rad = DX_PI_F / 180 * j;
			MATRIX rotX = MGetRotX(rad);
			VECTOR temp = vertex.at(i);
	
			ans.emplace_back(temp * rotX);
		}
		diameter.emplace_back(ans);
	}

	for (VECTOR& ver : vertex)
		ver = ver + transform.position;

	for(std::vector<VECTOR>&temp:diameter)
		for(VECTOR& ver:temp)
			ver = ver + transform.position;
}

void Sphere::Update(){

}

void Sphere::Draw(){
	transform.MakeMatrix();

	//for(VECTOR& ver:vertex)
	//	DrawPixel3D(ver,0xffffff);

	for (std::vector<VECTOR>& temp : diameter)
		for (VECTOR& ver : temp)
			DrawPixel3D(ver, 0xffffff);
	//DrawSphere3D(transform.position, 200, 10, 0xff0000, 0xff0000, true);
}
