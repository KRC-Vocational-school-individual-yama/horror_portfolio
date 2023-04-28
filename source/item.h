#pragma once
#include"libs/object.h"

class Item :public Object {
public:
	Item(Scene* sc);
	~Item()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	Transform transform;
	bool ons = false;
};