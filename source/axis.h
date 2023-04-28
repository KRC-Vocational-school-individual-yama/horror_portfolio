#pragma once
#include"libs/object.h"

class Axis :public Object {
public:
	Axis(Scene* sc);
	~Axis()			override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:

};