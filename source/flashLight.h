#pragma once
#include"libs/object.h"

/// <summary>
/// ���C�g�Ɋւ���N���X
/// �����d������肽������
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
