#pragma once
#include"libs/object.h"
class GraphDraw :public Object {
public:
	GraphDraw(Scene* sc);
	~GraphDraw()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;
private:

};