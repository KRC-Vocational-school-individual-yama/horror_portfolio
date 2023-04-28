#include "sinwave.h"
#include"keystate.h"

namespace {
	KeyState* upKey;
	KeyState* downKey;
	KeyState* saveKey;
}

SinWave::SinWave(Scene* sc)
	:Object(sc)
	,count(-1)
	,pos()
	,fastPos()
	,keystop()
	,splitNum(36)
	,circlePos()
{
	circlePos.clear();
}
SinWave::~SinWave(){

}
void SinWave::Init(){
	fastPos = {SCREEN_WIDTH/2,0,SCREEN_HEIGHT/2};

	upKey	= new KeyState(KEY_INPUT_W);
	downKey = new KeyState(KEY_INPUT_S);
	saveKey = new KeyState(KEY_INPUT_T);
	circlePos.resize(splitNum + 1);
}
void SinWave::Update(){
	//ï™äÑêîÇÃïœçX
	SplitChange();
	
	if(CheckHitKey(KEY_INPUT_O))
	if (count <= Circumference)
		count++;


	IncreaseVertex();


	upKey->Update();
	downKey->Update();
	saveKey->Update();
}
void SinWave::Draw(){
	DrawFormatString(50,50,0xffffff,"count=  %d",count);
	DrawFormatString(50,70,0xffffff,"ï™äÑêî= %d",splitNum);

	DrawSphere3D(VGet(0,0,0),25,3,0xffffff,0xffffff,false);

	for (VECTOR& p : pos) {
		DrawCircle(p.x,p.z,2,0xffffff,false);
	}

	for (auto it_all = circlePos.begin(); it_all != circlePos.end(); it_all++) {
		for (auto it_parent = (*it_all).begin(); it_parent != (*it_all).end(); ) {

			const VECTOR& p1 = (*it_parent);

			it_parent++;
			if (it_parent == (*it_all).end())continue;

			const VECTOR& p2 = (*it_parent);


			DrawLine3D(p1, p2, 0xffffff);
			DrawSphere3D(p1, 2, 30, 0xffffff, 0xffffff, true);
		}
	}
	for (auto it_all = circlePos.begin(); it_all != circlePos.end(); it_all++) {
		auto it_next = it_all;
		it_next++;
		if (it_next == circlePos.end())continue;
		if ((*it_next).empty())continue;

		//true turn
		{
			auto it_parent_next = (*it_next).begin();
			for (auto it_parent = (*it_all).begin(); it_parent != (*it_all).end(); it_parent++, it_parent_next++) {
				const VECTOR& p1 = (*it_parent);
				const VECTOR& p2 = (*it_parent_next);
				DrawLine3D(p1, p2, 0xffffff);
			}
		}

		////reverse turn
		//{
		//	auto it_parent_next = (*it_next).rbegin();
		//	for (auto it_parent = (*it_all).begin(); it_parent != (*it_all).end(); it_parent++, it_parent_next++) {
		//		const VECTOR& p1 = (*it_parent);
		//		const VECTOR& p2 = (*it_parent_next);
		//		DrawLine3D(p1, p2, 0xffffff);
		//	}
		//}
	}
	//std::vector<VECTOR>p(pos.begin(), pos.end());
	//std::vector<VECTOR>pp(pos2.begin(), pos2.end());

	//for (int i = 0; i < p.size(); i++) {
	//	VECTOR p1 = p.at(i);
	//	VECTOR p2 = p.at((i+1)%p.size());
	//
	//	//DrawLine(p1.x,p1.z,p2.x,p2.z,0xffffff);
	//
	//	DrawLine3D(p1,p2,0xffffff);
	//	DrawSphere3D(p1,2,30,0xffffff,0xffffff,true);
	//
	//	p1 = pp.at(i);
	//	p2 = pp.at((i + 1) % pp.size());
	//	DrawLine3D(p1,p2,0xffffff);
	//	DrawSphere3D(p1, 2, 30, 0xffffff, 0xffffff, true);
	//
	//}

	//for (int i = 0; i < p.size(); i++) {
	//	VECTOR p1 = p.at(i);
	//	VECTOR p2 = pp.at(i);
	//
	//	DrawLine3D(p1,p2,0xffffff);
	//}
	//
	//for (int i = 0; i < p.size(); i++) {
	//	VECTOR p1 = p.at(i);
	//	int index = (pos.size() - 1) - i;
	//	//index = max(index,pos.size()-1);
	//	VECTOR p2 = pp.at(index);
	//
	//	DrawLine3D(p1,p2,0xffffff);
	//}


	//int maxNumber = p.size();//36
	//for (int number = 0; number < maxNumber; number++) {
	//	VECTOR p1 = p.at(number);
	//	int reverseNumber = (maxNumber - 1) - number;
	//	//reverseNumber = max(reverseNumber,pos.size()-1);
	//	VECTOR p2 = pp.at(reverseNumber);
	//
	//	DrawLine3D(p1,p2,0xffffff);
	//}

	//DrawLine3D(VGet(0,0,0),VGet(0,100,0),0xffffff);
	//DrawLine3D(VGet(0,0,0),VGet(0,100,100),0xffffff);
}

void SinWave::SplitChange() {
	if (upKey->Down() && saveKey->Get()) {
		splitNum++;
	}
	if (downKey->Down() && saveKey->Get()) {
		splitNum = max(splitNum - 1, 1);
	}
	bool allKey = (upKey->Down() || downKey->Down()) && saveKey->Get();
	if (allKey) {
		count = 0;
		pos.clear();
		pos2.clear();
		for (std::list<VECTOR>p : circlePos)
			p.clear();
		circlePos.clear();
		circlePos.resize(splitNum + 1);
	}
}

void SinWave::IncreaseVertex(){

	if (count % (Circumference / splitNum) != 0)return;

	//auto it = circlePos.begin();
	//
	//VECTOR p = { 0,0 };
	//p.x = cos(DX_PI / 180 * count) * 200;
	//p.z = sin(DX_PI / 180 * count) * 200;
	//p = VAdd(p, fastPos);
	//(*it).emplace_back(p);
	////pos.emplace_back(p);
	//
	//VECTOR p2 = { 0,0 };
	//p2.x = cos(DX_PI / 180 * count) * 200;
	//p2.y = sin(DX_PI / 180 * count) * 200;
	//p2 = VAdd(p2, fastPos);
	//it++;
	//(*it).emplace_back(p2);
	////pos2.emplace_back(p2);

	int i = 0;
	for (auto it = circlePos.begin(); it != circlePos.end(); it++) {
		//for (int i = 0; i < splitNum ; i++) {
			MATRIX rotX = MGetRotX(DX_PI_F/180*(Circumference/ (i+1)));
			MATRIX rotY = MGetRotY(DX_PI_F / 180 * (count));
			//MScale(rotY,200);
			VECTOR p = VTransform(VGet(0, 0, -1), MScale(MMult(rotX,rotY), 200));

			p = VAdd(p, fastPos);
			(*it).emplace_back(p);
		//}
		i++;
	}

}
