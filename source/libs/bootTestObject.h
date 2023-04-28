#pragma once

#include"object.h"

class BootTestObject :public Object {
public:
	BootTestObject(Scene* sc);
	~BootTestObject()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	void Move()				;//���͎�t
	void Dash()				;//���肩������
	void SceneChangeKey()	;//�V�[���̐؂�ւ���t

	std::string freeStr		;//�Z���t
	Vec2 player				;//���W
	int radius				;
	int speed				;
};