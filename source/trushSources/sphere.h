#pragma once
#include"libs/object.h"

class Sphere :public Object {
public:
	Sphere(Scene* sc);
	~Sphere()		override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:
	Transform transform;

	std::vector<VECTOR>vertex;
	std::vector<std::vector<VECTOR>>diameter;
};