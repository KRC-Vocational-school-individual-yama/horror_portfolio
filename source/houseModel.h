#pragma once
#include"libs/object.h"
/// <summary>
/// �ƂƏ��̃��f��
/// </summary>
class HouseModel :public Object {
public:
	HouseModel(Scene* sc);
	~HouseModel()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	int hModel;
};