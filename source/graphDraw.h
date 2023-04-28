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
	int hImage;
	VECTOR dispPos;
	VECTOR size;
	Vec2 divNum;
	VERTEX3D* ver;

	int GetIndex(int _i, int _j);
	int GetVertexIndex(int num,int index);

	void VertexIn(std::vector<std::vector<VECTOR>>& vertexList);
};