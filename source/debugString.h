#pragma once
#include"libs/object.h"

/// <summary>
/// ƒŠƒŠ[ƒX‚É‚·‚é‚ÆÁ‚¦‚é•¶š
/// </summary>
class DebugString :public Object {
public:
	DebugString(Scene* sc);
	~DebugString()	override;
	void Init()		override;
	void Update()	override;
	void Draw()		override;

	void SetString(std::string _str,unsigned int _col = 0xffffff);
private:
	struct StringParam{
		std::string str="";
		unsigned int color=0;
		int number=0;
	};
	std::list<StringParam>strings;

};