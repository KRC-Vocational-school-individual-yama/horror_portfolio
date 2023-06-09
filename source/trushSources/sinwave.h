#pragma once
#include"libs/object.h"

class SinWave :public Object {
public:
	SinWave(Scene* sc);
	~SinWave()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	std::list<VECTOR>pos;
	std::list<VECTOR>pos2;
	std::list<std::list<VECTOR>>circlePos;
	VECTOR fastPos;
	int count;
	int splitNum;
	static const int Circumference = 360;
	bool keystop;


	//分割数の変更
	void SplitChange();
	//頂点を増やしていく
	void IncreaseVertex();
};