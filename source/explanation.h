#pragma once
#include"libs/object.h"

/// <summary>
/// à–¾‘—Ş
/// </summary>
class Explanation:public Object {
public:
	Explanation(Scene* sc);
	~Explanation()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

private:
	int hImage;
	int fontHandle;

	int backFontHandle;
	std::string str;
};