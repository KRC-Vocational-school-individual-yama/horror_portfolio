#pragma once
#include"libs/object.h"

class Door :public Object {
public:
	Door(Scene* sc);
	~Door();
	void Init();
	void Update();
	void Draw();

	void Open();
private:
	int hModel;
	float animCount;
	int animMaxCount;
	Transform transform;
	 int hAnimNumber;


	std::string InValueToString(VECTOR v);

	//NumPad3�ō��W��text�ɏ����o��
	void TextOutput();
	//�ړ��@���W�����p
	void Move();
};