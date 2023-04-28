#pragma once
#include"libs/object.h"
class SkyBox :public Object {
public:
	SkyBox(Scene* sc);
	~SkyBox()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	auto& GetSphereVertex() { return dispSphereList; }
	void GetDivNum(int& x, int& y);
private:
	int divNum;
	int Light;
	std::vector<std::vector<VECTOR>>sphereList;
	std::vector<std::vector<VECTOR>>dispSphereList;
	
};