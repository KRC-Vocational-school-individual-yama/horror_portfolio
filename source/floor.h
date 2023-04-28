#pragma once
#include"libs/object.h"

class Floor :public Object {
public:
	Floor(Scene* sc);
	~Floor()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	std::vector<int>hImage;
};