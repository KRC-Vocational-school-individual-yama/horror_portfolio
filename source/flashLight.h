#pragma once
#include"libs/object.h"

/// <summary>
/// ライトに関するクラス
/// 懐中電灯が作りたかった
/// </summary>
class FlashLight :public Object {
public:
	FlashLight(Scene* sc);
	~FlashLight()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	int lightHandle;
	int lightHandle2;
	bool on;
};
