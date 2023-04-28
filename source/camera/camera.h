#pragma once
#include"../libs/object.h"

/// <summary>
/// ���R�J����
/// </summary>
class Camera :public Object {
public:
	Camera(Scene* sc);
	~Camera()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	//�J�������W
	const VECTOR& GetPos() { return position; }
	//�J���������x�N�g��
	VECTOR GetDir();
	//const VECTOR& GetRot() { return rotation; }
private:
	void DispMove();
	void UpDownMove();
	void Movement();


	VECTOR position;
	VECTOR target;
	VECTOR tarPos;
	VECTOR velocity;
	VECTOR rotation;
	Vec2 mouse;
	Vec2 oldMouse;

};