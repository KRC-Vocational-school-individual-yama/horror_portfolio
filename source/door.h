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

	//NumPad3で座標をtextに書き出す
	void TextOutput();
	//移動　座標調整用
	void Move();
};